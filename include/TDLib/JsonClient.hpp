#ifndef TDLIB_JSONCLIENT_H
#define TDLIB_JSONCLIENT_H

#include <phpcpp.h>
#include <nlohmann/json.hpp>
#include "BaseJsonClient.hpp"
#include "../TDApi/TDLibParameters.hpp"

class JsonClient : public BaseJsonClient {
private:
    std::string lastResponse;
    std::vector<std::string> receivedResponses;
    std::vector<nlohmann::json> receivedResponsesExtras;
    double defaultTimeout = 0.5;

    void handleResponses(nlohmann::json *breakOnExtra);

    std::string waitForResponse(nlohmann::json *extra, double timeout);

public:

    // exported
    // BaseJsonClient
    inline void __construct(Php::Parameters &params) override { BaseJsonClient::__construct(params); };

    inline void __destruct() override { BaseJsonClient::__destruct(); };

    inline Php::Value execute(Php::Parameters &params) override { return BaseJsonClient::execute(params); }

    inline void send(Php::Parameters &params) override { BaseJsonClient::send(params); }

    Php::Value receive(Php::Parameters &params) override;

    // JsonClient
    std::string query(const char *query, double timeout, nlohmann::json *extra);

    Php::Value query(Php::Parameters &params);

    Php::Value query(const std::string &requestString, double timeout);

    std::string addExtraAndSendQuery(const std::string &type, nlohmann::json *jsonQuery, double timeout);

    Php::Value getReceivedResponses(Php::Parameters &params);

    void setDefaultTimeout(Php::Parameters &params);

    // tdlib Function Class Reference
    Php::Value checkDatabaseEncryptionKey(Php::Parameters &params);

    Php::Value getAuthorizationState(Php::Parameters &params);

    Php::Value setAuthenticationPhoneNumber(Php::Parameters &params);

    Php::Value setDatabaseEncryptionKey(Php::Parameters &params);

    Php::Value setTdlibParameters(Php::Parameters &params);

    std::string setTdlibParameters(TDLibParameters *parameters, double timeout);
};

#endif // TDLIB_JSONCLIENT_H