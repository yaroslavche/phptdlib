#include <iostream>

#include <phpcpp.h>

#include "JsonClient.hpp"

#include "../TDApi/TDLibParameters.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

Php::Value JsonClient::query(Php::Parameters &params)
{
    const char *queryParam = params[0];
    double timeout = params[1];
    std::string result = query(queryParam, timeout);
    return result;
}

std::string JsonClient::query(const char *query, double timeout)
{
    // auto queryData = json::parse(query);
    // Php::out << queryData << std::endl;
    BaseJsonClient::send(query);
    std::string result;
    try
    {
        while(true)
        {
            auto tmpResult = BaseJsonClient::receive(timeout);
            Php::out << tmpResult << std::endl;
            if (!tmpResult.empty()) {
                result = tmpResult;
                auto resultJson = json::parse(tmpResult);
                if(resultJson["@type"] == "updateAuthorizationState") authorizationState = resultJson["authorization_state"]["@type"];
                // if(j["@type"] == "ok") break;
                // if(j["@type"] == "error") break;
                // if(j["@type"] == "authorizationStateWaitTdlibParameters") break;
                // if(j["@type"] == "authorizationStateWaitPhoneNumber") break;
                // if(j["@type"] == "updateConnectionState" && j["state"]["@type"] == "connectionStateReady") break;
            }
        }
    }
    catch(...)
    {
        Php::out << "EXCEPTION" << std::endl << std::endl;
    }
    return result;
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
    const std::string jsonQuery = "{\"@type\":\"checkDatabaseEncryptionKey\", \"key\":\"" + key + "\"}";
    std::string result = query(jsonQuery.c_str(), defaultTimeout);
    return result;
}

Php::Value JsonClient::setDatabaseEncryptionKey(Php::Parameters &params)
{
    const std::string new_encryption_key = !params.empty() ? params[0] : "";
    const std::string jsonQuery = "{\"@type\":\"setDatabaseEncryptionKey\"" + (new_encryption_key.length() > 0 ? ",\"new_encryption_key\":\"" + new_encryption_key + "\"" : "") + "}";
    std::string result = query(jsonQuery.c_str(), defaultTimeout);
    return result;
}

Php::Value JsonClient::getAuthorizationState(Php::Parameters &params)
{
    // double extra = params[0];
    const char *jsonQuery = "{\"@type\":\"getAuthorizationState\",\"@extra\":0.1234}";
    std::string result = query(jsonQuery, defaultTimeout);
    return result;
}

Php::Value JsonClient::setAuthenticationPhoneNumber(Php::Parameters &params)
{
    std::string phone_number = params[0];
    std::string jsonQuery = "{\"@type\":\"setAuthenticationPhoneNumber\", \"phone_number\":\"" + phone_number + "\"}";
    std::string result = query(jsonQuery.c_str(), defaultTimeout);
    return result;
}
