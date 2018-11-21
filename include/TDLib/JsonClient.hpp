#ifndef TDLIB_JSONCLIENT_H
#define TDLIB_JSONCLIENT_H

#include <nlohmann/json.hpp>
#include "BaseJsonClient.hpp"

class JsonClient : public BaseJsonClient
{
    private:
        // todo: lastResponse json object
        std::string lastResponse;
        std::vector<std::string> receivedResponses;
        std::vector<nlohmann::json> receivedResponsesExtras;
        std::string authorizationState;
        std::string connectionState;
        double defaultTimeout = 0.5;

        void handleResponses(nlohmann::json* breakOnExtra);
        std::string waitForResponse(nlohmann::json* extra,double timeout);

    public:
        std::string query(const char *query, double timeout, nlohmann::json* extra);

        // exported
        Php::Value query(Php::Parameters &params);
        Php::Value setTdlibParameters(Php::Parameters &params);
        Php::Value setDatabaseEncryptionKey(Php::Parameters &params);
        Php::Value checkDatabaseEncryptionKey(Php::Parameters &params);
        Php::Value getAuthorizationState(Php::Parameters &params);
        Php::Value setAuthenticationPhoneNumber(Php::Parameters &params);
        Php::Value getReceivedResponses(Php::Parameters &params);

        void setDefaultTimeout(Php::Parameters &params);

        inline void create() { BaseJsonClient::create(); }
        inline void destroy() { BaseJsonClient::destroy(); }
        inline Php::Value execute(Php::Parameters &params) { BaseJsonClient::execute(params); }
        inline void send(Php::Parameters &params) { BaseJsonClient::send(params); }
        Php::Value receive(Php::Parameters &params);
        inline void __construct(Php::Parameters &params) { BaseJsonClient::__construct(params);};
        inline void __destruct() { BaseJsonClient::__destruct();};

        // internal

};

#endif // TDLIB_JSONCLIENT_H
