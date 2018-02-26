#include <phpcpp.h>
#include <iostream>
#include <td/telegram/tdjson_export.h>
#include <td/telegram/td_json_client.h>

void *client;

Php::Value tdlib_version()
{
    return "0.0.1";
}

Php::Value tdlib_td_json_client_create()
{
    client = td_json_client_create();
    return client;
}

void tdlib_td_json_client_send(Php::Parameters &params)
{
    // client
    // string request
    td_json_client_send(client, params[1]);
    return;
}

Php::Value tdlib_td_json_client_receive(Php::Parameters &params)
{
    // client
    double timeout = params[1];
    std::string receive = td_json_client_receive(client, timeout);
    return receive;
}

Php::Value tdlib_td_json_client_execute(Php::Parameters &params)
{
    // client
    // string request
    return "td_json_client_execute";
}

void tdlib_td_json_client_destroy(Php::Parameters &params)
{
    // client
    return;
}

extern "C" {

    PHPCPP_EXPORT void *get_module()
    {
        static Php::Extension tdlib("tdlib", "0.0.1");
        tdlib.add<tdlib_version>("td_version");
        tdlib.add<tdlib_td_json_client_create>("td_json_client_create");
        tdlib.add<tdlib_td_json_client_send>("td_json_client_send");
        tdlib.add<tdlib_td_json_client_receive>("td_json_client_receive");
        tdlib.add<tdlib_td_json_client_execute>("td_json_client_execute");
        tdlib.add<tdlib_td_json_client_destroy>("td_json_client_destroy");
        return tdlib;
    }
}
