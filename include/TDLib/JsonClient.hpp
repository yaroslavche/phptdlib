#ifndef TDLIB_JSONCLIENT_H
#define TDLIB_JSONCLIENT_H

#include "BaseJsonClient.hpp"

class JsonClient : public BaseJsonClient
{
    private:
        std::string authorizationState;
        std::string connectionState;
        double defaultTimeout = 0.5;

    public:
        std::string query(const char *query, double timeout);

        // exported
        Php::Value query(Php::Parameters &params);
        Php::Value setTdlibParameters(Php::Parameters &params);
        Php::Value setDatabaseEncryptionKey(Php::Parameters &params);
        Php::Value checkDatabaseEncryptionKey(Php::Parameters &params);
        Php::Value getAuthorizationState(Php::Parameters &params);
        Php::Value setAuthenticationPhoneNumber(Php::Parameters &params);

        void setDefaultTimeout(Php::Parameters &params) { Php::warning << "implement" << std::flush; };

        inline void create() { BaseJsonClient::create(); }
        inline void destroy() { BaseJsonClient::destroy(); }
        inline Php::Value execute(Php::Parameters &params) { BaseJsonClient::execute(params); }
        inline void send(Php::Parameters &params) { BaseJsonClient::send(params); }
        inline Php::Value receive(Php::Parameters &params) { BaseJsonClient::receive(params); }

        // internal

};

#endif // TDLIB_JSONCLIENT_H
