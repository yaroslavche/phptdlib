#ifndef TDLIB_JSONCLIENT_H
#define TDLIB_JSONCLIENT_H

#include "BaseJsonClient.hpp"

class JsonClient : public BaseJsonClient
{
    private:
        double defaultTimeout = 10;

    public:
        std::string query(const char *query, double timeout);

        // exported
        Php::Value query(Php::Parameters &params);
        Php::Value setTdlibParameters(Php::Parameters &params);
        Php::Value setDatabaseEncryptionKey(Php::Parameters &params);
        Php::Value getAuthorizationState(Php::Parameters &params);

        void setDefaultTimeout(Php::Parameters &params) { };

        inline void create() { BaseJsonClient::create(); }
        inline void destroy() { BaseJsonClient::destroy(); }
        inline Php::Value execute(Php::Parameters &params) {  }
        inline void send(Php::Parameters &params) {  }
        inline Php::Value receive(Php::Parameters &params) {  }

};

#endif // TDLIB_JSONCLIENT_H
