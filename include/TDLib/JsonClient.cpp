#include <iostream>
#include <chrono>
#include <thread>

#include <phpcpp.h>

#include "JsonClient.hpp"

#include "../common.hpp"

using json = nlohmann::json;

void JsonClient::handleResponses(json *breakOnExtra) {
    while (true) {
        try {
            lastResponse = BaseJsonClient::receive(0);
        }
        catch (const std::exception &e) {
            break;
        }

        if (lastResponse.empty()) {
            break;
        } else {
            auto responseJson = json::parse(lastResponse);

            std::string responseCopy(lastResponse);
            receivedResponses.push_back(responseCopy);

            int hasExtraInResponse = responseJson.find("@extra") != responseJson.end();
            if (hasExtraInResponse) {
                receivedResponsesExtras.push_back(responseJson["@extra"]);
            } else {
                receivedResponsesExtras.emplace_back(0);
            }
            if (breakOnExtra != nullptr && hasExtraInResponse && (*breakOnExtra) == responseJson["@extra"]) {
                break;
            }
        }
    }
}

std::string JsonClient::waitForResponse(json *extra, double timeout) {
    std::vector<nlohmann::json>::iterator itExtras;
    std::vector<std::string>::iterator itResponses;

    std::chrono::time_point<std::chrono::high_resolution_clock>
            currentTime,
            startedAt = std::chrono::high_resolution_clock::now();

    bool repeat;

    int scannedResponses = 0;

    do {
        handleResponses(extra);

        if (receivedResponsesExtras.size() > scannedResponses) {
            itExtras = std::next(receivedResponsesExtras.begin(), scannedResponses);
            itResponses = std::next(receivedResponses.begin(), scannedResponses);

            for (; itExtras != receivedResponsesExtras.end() &&
                   (*itExtras) != (*extra); itExtras++, itResponses++, scannedResponses++) {
            }
            if (itExtras != receivedResponsesExtras.end()) {
                return *itResponses;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(3));

        currentTime = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startedAt);
        repeat = (time.count() < (int) (timeout * 1000.));
    } while (repeat);

    throw Php::Exception("Timeout waiting for response");
}

std::string JsonClient::query(const char *query, double timeout, json *extra) {
    BaseJsonClient::send(query);
    return waitForResponse(extra, timeout);
    // todo: lastQuery [lastRequest, lastResponse, isSuccess, state] ?
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc30-c"

std::string JsonClient::addExtraAndSendQuery(const std::string &type, json *jsonQuery, double timeout) {
    json extra;
    auto extraIt = jsonQuery->find("@extra");
    if (extraIt == jsonQuery->end()) {
        /*
        struct timespec ts{};
        if (timespec_get(&ts, TIME_UTC) == 0) {
            // Handle error
        }
        srandom(ts.tv_nsec ^ ts.tv_sec);
        extra = random();
        */
        extra = rand();
        (*jsonQuery)["@extra"] = extra;
    } else {
        extra = extraIt.value();
    }

    (*jsonQuery)["@type"] = type;

    return query(jsonQuery->dump().c_str(), timeout, &extra);
}

#pragma clang diagnostic pop

/**
* exported
**/

Php::Value JsonClient::receive(Php::Parameters &params) {
    double timeout = getPhpFunctionArgument(params, 0, defaultTimeout);
    return BaseJsonClient::receive(timeout);
}

Php::Value JsonClient::query(Php::Parameters &params) {
    std::string requestString = getPhpFunctionArgument(params, 0, "");
    double timeout = getPhpFunctionArgument(params, 1, defaultTimeout);
    return query(requestString, timeout);
}

Php::Value JsonClient::query(const std::string &requestString, double timeout) {
    json request;

    try {
        request = json::parse(requestString);
    }
    catch (nlohmann::json::exception &exception) {
        throw Php::Exception("Error parsing json");
    }

    auto typeIt = request.find("@type");
    if (typeIt == request.end()) {
        throw Php::Exception("Empty @type in query");
    }

    if (!typeIt->is_string()) {
        throw Php::Exception("Parameter @type should be string");
    }

    std::string type = *typeIt;

    return addExtraAndSendQuery(
            type,
            &request,
            timeout
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
    defaultTimeout = getPhpFunctionArgument(params, 0, 0.0);
}

/**
* tdlib Function Class Reference
**/

Php::Value JsonClient::checkDatabaseEncryptionKey(Php::Parameters &params) {
    const std::string key = getPhpFunctionArgument(params, 0, "");
    json jsonQuery;
    jsonQuery["key"] = key;

    return addExtraAndSendQuery(
            "checkDatabaseEncryptionKey",
            &jsonQuery,
            getPhpFunctionArgument(params, 1, defaultTimeout)
    );
}

Php::Value JsonClient::getAuthorizationState(Php::Parameters &params) {
    json jsonQuery;

    return addExtraAndSendQuery(
            "getAuthorizationState",
            &jsonQuery,
            getPhpFunctionArgument(params, 0, defaultTimeout)
    );
}

Php::Value JsonClient::setAuthenticationPhoneNumber(Php::Parameters &params) {
    std::string phone_number = getPhpFunctionArgument(params, 0, "");
    json jsonQuery;
    jsonQuery["phone_number"] = phone_number;

    return addExtraAndSendQuery(
            "setAuthenticationPhoneNumber",
            &jsonQuery,
            getPhpFunctionArgument(params, 1, defaultTimeout)
    );
}

Php::Value JsonClient::setDatabaseEncryptionKey(Php::Parameters &params) {
    const std::string new_encryption_key = getPhpFunctionArgument(params, 0, "");
    json jsonQuery;
    if (new_encryption_key.length() > 0) jsonQuery["new_encryption_key"] = new_encryption_key;

    return addExtraAndSendQuery(
            "setDatabaseEncryptionKey",
            &jsonQuery,
            getPhpFunctionArgument(params, 1, defaultTimeout)
    );
}

std::string JsonClient::setTdlibParameters(TDLibParameters *parameters, double timeout) {
    json parametersJson = parameters->getParameters();

    json jsonQuery;
    jsonQuery["parameters"] = parametersJson;

    return addExtraAndSendQuery(
            "setTdlibParameters",
            &jsonQuery,
            timeout
    );
}

Php::Value JsonClient::setTdlibParameters(Php::Parameters &params) {
    Php::Value tdlibParams = getPhpFunctionArgument(params, 0);
    if (!tdlibParams.instanceOf("TDApi\\TDLibParameters")) {
        throw Php::Exception("First parameter must be instance of TDApi\\TDLibParameters.");
    }

    auto *parametersObject = (TDLibParameters *) tdlibParams.implementation();

    return setTdlibParameters(
            parametersObject,
            getPhpFunctionArgument(params, 1, defaultTimeout)
    );
}
