#include <iostream>
#include <chrono>
#include <thread>

#include <phpcpp.h>

#include "JsonClient.hpp"

#include "../TDApi/TDLibParameters.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

// todo: constructor with query like getAuthorizationState by default (possibility to disable)

Php::Value JsonClient::query(Php::Parameters &params)
{
    const char *queryParam = params[0];
    double timeout = params[1];
    std::string result = query(queryParam, timeout);
    return result;
}

std::string JsonClient::query(const char *query, double timeout)
{
    // Php::out << "handle before query: " << query << std::endl << std::endl;
    handleResponses();
    // checkAuthorizationState();
    // Php::out << "send query: " << query << std::endl << std::endl;
    BaseJsonClient::send(query);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    // Php::out << "handle after query: " << query << std::endl << std::endl;
    handleResponses();
    // Php::out << "return with response \"" << lastResponse << "\" to query: " << query << std::endl << std::endl;
    return lastResponse;
    // todo: lastQuery [lastRequest, lastResponse, isSuccess, state] ?
}

Php::Value JsonClient::getReceivedResponses(Php::Parameters &params)
{
    handleResponses();
    std::vector<std::string> oldResponses(receivedResponses);
    receivedResponses.clear();
    return oldResponses;
}

void JsonClient::handleResponses()
{
    while(true)
    {
        try
        {
            lastResponse = BaseJsonClient::receive(0);
        }
        catch(const std::exception& e)
        {
            // todo handle exceptions
            // basic_string::_M_construct null not valid
            // Php::out << "exception " << e.what() << std::endl << std::endl;
            break;
        }
        if (lastResponse.empty()) break;
        auto responseJson = json::parse(lastResponse);
        // Php::out << "handle response: " << responseJson << std::endl << std::endl;
        if(responseJson["@type"] == "ok") ;
        if(responseJson["@type"] == "error") ;
        if(responseJson["@type"] == "updateAuthorizationState") authorizationState = responseJson["authorization_state"]["@type"];
        if(responseJson["@type"] == "updateOption") ;
        if(responseJson["@type"] == "updateConnectionState") ;
        std::string responseCopy(lastResponse);
        receivedResponses.push_back(responseCopy);
    }
}

Php::Value JsonClient::setTdlibParameters(Php::Parameters &params)
{
    Php::Value tdlibParams = params[0];
    if(!tdlibParams.instanceOf("TDApi\\TDLibParameters")) throw Php::Exception("First parameter must be instance of TDApi\\TDLibParameters.");
    TDLibParameters *parameters = (TDLibParameters *)tdlibParams.implementation();
    std::string parametersJsonQuery = parameters->toJsonQuery();
    std::string result = query(parametersJsonQuery.c_str(), defaultTimeout);
    return result;
}

Php::Value JsonClient::checkDatabaseEncryptionKey(Php::Parameters &params)
{
    const std::string key = params[0];
    json jsonQuery;
    jsonQuery["@type"] = "checkDatabaseEncryptionKey";
    jsonQuery["key"] = key;
    std::string result = query(jsonQuery.dump().c_str(), defaultTimeout);
    return result;
}

Php::Value JsonClient::setDatabaseEncryptionKey(Php::Parameters &params)
{
    const std::string new_encryption_key = !params.empty() ? params[0] : "";
    json jsonQuery;
    jsonQuery["@type"] = "setDatabaseEncryptionKey";
    if(new_encryption_key.length() > 0) jsonQuery["new_encryption_key"] = new_encryption_key;
    std::string result = query(jsonQuery.dump().c_str(), defaultTimeout);
    return result;
}

Php::Value JsonClient::getAuthorizationState(Php::Parameters &params)
{
    // double extra = params[0];
    json jsonQuery;
    jsonQuery["@type"] = "getAuthorizationState";
    std::string result = query(jsonQuery.dump().c_str(), defaultTimeout);
    return result;
}

Php::Value JsonClient::setAuthenticationPhoneNumber(Php::Parameters &params)
{
    std::string phone_number = params[0];
    json jsonQuery;
    jsonQuery["@type"] = "setAuthenticationPhoneNumber";
    jsonQuery["phone_number"] = phone_number;
    std::string result = query(jsonQuery.dump().c_str(), defaultTimeout);
    return result;
}
