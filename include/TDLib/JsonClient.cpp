#include <iostream>
#include <chrono>
#include <thread>

#include <phpcpp.h>

#include "JsonClient.hpp"

#include "../TDApi/TDLibParameters.hpp"

using json = nlohmann::json;

// todo: constructor with query like getAuthorizationState by default (possibility to disable)

Php::Value JsonClient::query(Php::Parameters &params)
{
    std::string requestString = params[0];
    double timeout=defaultTimeout;
    if(params.size()>1) {
        timeout = params[1];
    }

    json request=json::parse(requestString);

    auto extraIt = request.find("@extra");
    json extra=0;
    if (extraIt == request.end())
    {
        extra=rand();
        request["@extra"] = extra;
    } else {
        extra=extraIt.value();
    }

    std::string result = query(request.dump().c_str(), timeout, &extra);
    return result;
}

std::string JsonClient::query(const char *query, double timeout, json* extra)
{
    BaseJsonClient::send(query);
    return waitForResponse(extra, timeout);
    // todo: lastQuery [lastRequest, lastResponse, isSuccess, state] ?
}

Php::Value JsonClient::getReceivedResponses(Php::Parameters &params)
{
    handleResponses(nullptr);
    std::vector<std::string> oldResponses(receivedResponses);
    receivedResponses.clear();
    receivedResponsesExtras.clear();
    return oldResponses;
}


std::string JsonClient::waitForResponse(json* extra,double timeout) {
    std::vector<nlohmann::json>::iterator itExtras;
    std::vector<std::string>::iterator itResponses;

    std::chrono::time_point<std::chrono::high_resolution_clock>
            currentTime,
            startedAt = std::chrono::high_resolution_clock::now();

    bool repeat;

    int scannedResponses=0;

    do {
        handleResponses(extra);

        if(receivedResponsesExtras.size()>scannedResponses) {
            itExtras=std::next(receivedResponsesExtras.begin(), scannedResponses);
            itResponses=std::next(receivedResponses.begin(), scannedResponses);

            for(;itExtras!=receivedResponsesExtras.end() && (*itExtras)!=(*extra);itExtras++,itResponses++,scannedResponses++) {
            }
            if(itExtras!=receivedResponsesExtras.end()) {
                return *itResponses;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(3));

        currentTime = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime-startedAt);
        repeat=(time.count()<(int)(timeout*1000.));
    } while(repeat);

    return "";
}



void JsonClient::handleResponses(json* breakOnExtra)
{
    while(true)
    {
        try
        {
            lastResponse = BaseJsonClient::receive(0);
        }
        catch(const std::exception& e)
        {
            break;
        }

        if (lastResponse.empty())
        {
            break;
        }
        else
        {
            auto responseJson = json::parse(lastResponse);
            if(responseJson["@type"] == "ok") ;
            if(responseJson["@type"] == "error") ;
            if(responseJson["@type"] == "updateAuthorizationState") authorizationState = responseJson["authorization_state"]["@type"];
            if(responseJson["@type"] == "updateOption") ;
            if(responseJson["@type"] == "updateConnectionState") ;

            std::string responseCopy(lastResponse);
            receivedResponses.push_back(responseCopy);

            int hasExtraInResponse=responseJson.find("@extra")!=responseJson.end();
            if(hasExtraInResponse) {
                receivedResponsesExtras.push_back(responseJson["@extra"]);
            } else {
                receivedResponsesExtras.push_back(0);
            }
            if(breakOnExtra != nullptr && hasExtraInResponse && (*breakOnExtra)==responseJson["@extra"]) {
                break;
            }
        }
    }
}

Php::Value JsonClient::setTdlibParameters(Php::Parameters &params)
{
    Php::Value tdlibParams = params[0];
    if(!tdlibParams.instanceOf("TDApi\\TDLibParameters")) throw Php::Exception("First parameter must be instance of TDApi\\TDLibParameters.");
    TDLibParameters *parameters = (TDLibParameters *)tdlibParams.implementation();
    std::string parametersJsonQuery = parameters->toJsonQuery();

    json extra = parameters->extraParameterValue;

    return query(parametersJsonQuery.c_str(), defaultTimeout, &extra);
}

Php::Value JsonClient::checkDatabaseEncryptionKey(Php::Parameters &params)
{
    const std::string key = params[0];
    json jsonQuery;
    jsonQuery["@type"] = "checkDatabaseEncryptionKey";
    jsonQuery["key"] = key;

    json extra = rand();
    jsonQuery["@extra"] = extra;

    return query(jsonQuery.dump().c_str(), defaultTimeout, &extra);
}

Php::Value JsonClient::setDatabaseEncryptionKey(Php::Parameters &params)
{
    const std::string new_encryption_key = !params.empty() ? params[0] : "";
    json jsonQuery;
    jsonQuery["@type"] = "setDatabaseEncryptionKey";
    if(new_encryption_key.length() > 0) jsonQuery["new_encryption_key"] = new_encryption_key;

    json extra = rand();
    jsonQuery["@extra"] = extra;

    return query(jsonQuery.dump().c_str(), defaultTimeout, &extra);
}

Php::Value JsonClient::getAuthorizationState(Php::Parameters &params)
{
    json jsonQuery;
    jsonQuery["@type"] = "getAuthorizationState";

    json extra = rand();
    jsonQuery["@extra"] = extra;

    return query(jsonQuery.dump().c_str(), defaultTimeout, &extra);
}

Php::Value JsonClient::setAuthenticationPhoneNumber(Php::Parameters &params)
{
    std::string phone_number = params[0];
    json jsonQuery;
    jsonQuery["@type"] = "setAuthenticationPhoneNumber";
    jsonQuery["phone_number"] = phone_number;

    json extra = rand();
    jsonQuery["@extra"] = extra;

    return query(jsonQuery.dump().c_str(), defaultTimeout, &extra);
}

void JsonClient::setDefaultTimeout(Php::Parameters &params)
{
    defaultTimeout = params[0];
}

Php::Value JsonClient::receive(Php::Parameters &params) {
    double timeout = defaultTimeout;
    if(params.size() > 0)
    {
        timeout = params[0];
    }
    return BaseJsonClient::receive(timeout);
}
