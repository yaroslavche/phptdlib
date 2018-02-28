#include "tdlib_json_client_func.hpp"
#include "tdlib_json_client.hpp"

/*
 * not working now
 */

Php::Value tdlib_td_json_client_create()
{
    TDLibJsonClient *clientResource = new TDLibJsonClient();
    clientResource->create();
    Php::Object client = Php::Object("TDLibJsonClient", clientResource);
    return client;
}

void tdlib_td_json_client_destroy(Php::Parameters &params)
{
    Php::Value object = params[0];
    if (!object.instanceOf("TDLibJsonClient")) throw Php::Exception("First argument must be an instance of TDLibJsonClient.");
    TDLibJsonClient *client = (TDLibJsonClient *)object.implementation();
    td_json_client_destroy(client->getPtr());
    return;
}

Php::Value tdlib_td_json_client_execute(Php::Parameters &params)
{
    void *client = params[0].implementation();
    const char *query = params[1];
    td_json_client_execute(client, query);
    return true;
}

Php::Value tdlib_td_json_client_send(Php::Parameters &params)
{
    Php::Value object = params[0];
    if (!object.instanceOf("TDLibJsonClient")) throw Php::Exception("First argument must be an instance of TDLibJsonClient.");
    TDLibJsonClient *client = (TDLibJsonClient *)object.implementation();
    const char *query = params[1];
    td_json_client_send(client->getPtr(), query);
    return true;
}

Php::Value tdlib_td_json_client_receive(Php::Parameters &params)
{
    void *client = params[0].implementation();
    double timeout = params[1];
    std::string str = td_json_client_receive(client, timeout);
    return str;
}

Php::Value tdlib_td_json_client_send_and_wait(Php::Parameters &params)
{
    void *client = params[0].implementation();
    const char *query = params[1];
    double timeout = params[2];
    td_json_client_send(client, query);
    while (true) {
        std::string str = td_json_client_receive(client, timeout);
        if (!str.empty()) {
            return str;
        }
    }
    return false;
}
