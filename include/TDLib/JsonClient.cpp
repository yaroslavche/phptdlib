#include <iostream>
#include <chrono>
#include <thread>

#include <phpcpp.h>

#include "JsonClient.hpp"

#include "../TDApi/TDLibParameters.hpp"

using json = nlohmann::json;

void JsonClient::handleResponses(json* breakOnExtra) {
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

std::string JsonClient::query(const char *query, double timeout, json* extra) {
    BaseJsonClient::send(query);
    return waitForResponse(extra, timeout);
    // todo: lastQuery [lastRequest, lastResponse, isSuccess, state] ?
}

std::string JsonClient::addExtraAndSendQuery(std::string type, json* jsonQuery, double timeout) {
    json extra;
    auto extraIt = jsonQuery->find("@extra");
    if (extraIt == jsonQuery->end())
    {
        extra=rand();
        (*jsonQuery)["@extra"] = extra;
    } else {
        extra=extraIt.value();
    }

    (*jsonQuery)["@type"] = type;

    return query(jsonQuery->dump().c_str(), timeout, &extra);
}

double JsonClient::getTimeoutFromParams(Php::Parameters &params, int timeoutParameterIndex) {
    if (params.size() <= timeoutParameterIndex)
    {
        return defaultTimeout;
    }

    return params[timeoutParameterIndex];
}

/**
* exported
**/

Php::Value JsonClient::receive(Php::Parameters &params) {
    double timeout = defaultTimeout;
    if(params.size() > 0)
    {
        timeout = params[0];
    }
    return BaseJsonClient::receive(timeout);
}

Php::Value JsonClient::query(Php::Parameters &params) {
    std::string requestString = params[0];
    json request;

    try {
        request=json::parse(requestString);
    } catch (nlohmann::json::exception exception) {
        throw Php::Exception("Error parsing json");
    }

    auto typeIt = request.find("@type");
    if (typeIt == request.end()) {
        throw Php::Exception("Empty @type in query");
    }

    if (! typeIt->is_string())
    {
        throw Php::Exception("Parameter @type should be string");
    }

    std::string type = *typeIt;

    return addExtraAndSendQuery(
            type,
            &request,
            getTimeoutFromParams(params, 1)
    );
}

Php::Value JsonClient::getReceivedResponses(Php::Parameters &params) {
    handleResponses(nullptr);
    std::vector<std::string> oldResponses(receivedResponses);
    receivedResponses.clear();
    receivedResponsesExtras.clear();
    return oldResponses;
}

void JsonClient::setDefaultTimeout(Php::Parameters &params) {
    defaultTimeout = params[0];
}

/**
* tdlib Function Class Reference
**/

Php::Value JsonClient::checkDatabaseEncryptionKey(Php::Parameters &params) {
    const std::string key = params[0];
    json jsonQuery;
    jsonQuery["key"] = key;

    return addExtraAndSendQuery(
            "checkDatabaseEncryptionKey",
            &jsonQuery,
            getTimeoutFromParams(params, 1)
    );
}

Php::Value JsonClient::getAuthorizationState(Php::Parameters &params) {
    json jsonQuery;

    return addExtraAndSendQuery(
            "getAuthorizationState",
            &jsonQuery,
            getTimeoutFromParams(params, 0)
    );
}

Php::Value JsonClient::setAuthenticationPhoneNumber(Php::Parameters &params) {
    std::string phone_number = params[0];
    json jsonQuery;
    jsonQuery["phone_number"] = phone_number;

    return addExtraAndSendQuery(
            "setAuthenticationPhoneNumber",
            &jsonQuery,
            getTimeoutFromParams(params, 1)
    );
}

Php::Value JsonClient::setDatabaseEncryptionKey(Php::Parameters &params) {
    const std::string new_encryption_key = !params.empty() ? params[0] : "";
    json jsonQuery;
    if(new_encryption_key.length() > 0) jsonQuery["new_encryption_key"] = new_encryption_key;

    return addExtraAndSendQuery(
            "setDatabaseEncryptionKey",
            &jsonQuery,
            getTimeoutFromParams(params, 1)
    );
}

Php::Value JsonClient::setTdlibParameters(Php::Parameters &params) {
    Php::Value tdlibParams = params[0];
    if(!tdlibParams.instanceOf("TDApi\\TDLibParameters")) throw Php::Exception("First parameter must be instance of TDApi\\TDLibParameters.");
    TDLibParameters *parametersObject = (TDLibParameters *)tdlibParams.implementation();

    json parameters = parametersObject->getParameters();

    json jsonQuery;
    jsonQuery["parameters"] = parameters;

    return addExtraAndSendQuery(
            "setTdlibParameters",
            &jsonQuery,
            getTimeoutFromParams(params, 1)
    );
}
