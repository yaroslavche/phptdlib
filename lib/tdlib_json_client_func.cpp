#include "tdlib_json_client_func.hpp"

Php::Value tdlib_td_json_client_create()
{
    void *client = td_json_client_create();
    return client;
}

void tdlib_td_json_client_destroy(Php::Parameters &params)
{
    void *client = params[0].implementation();
    td_json_client_destroy(client);
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
    void *client = params[0].implementation();
    const char *query = params[1];
    td_json_client_send(client, query);
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
