#include <phpcpp.h>
// #include "td/telegram/tdjson_export.h"

Php::Value td_json_client_create()
{
    return "create";
}

void td_json_client_send(Php::Parameters &params)
{
    // client
    // string request
    return;
}

Php::Value td_json_client_receive(Php::Parameters &params)
{
    // client
    // double timeout
    return "receive";
}

Php::Value td_json_client_execute(Php::Parameters &params)
{
    // client
    // string request
    return "execute";
}

void td_json_client_destroy(Php::Parameters &params)
{
    // client
    return;
}

extern "C" {

    PHPCPP_EXPORT void *get_module()
    {
        static Php::Extension tdlib("tdlib", "0.0.1");
        tdlib.add<td_json_client_create>("td_json_client_create");
        tdlib.add<td_json_client_send>("td_json_client_send");
        tdlib.add<td_json_client_receive>("td_json_client_receive");
        tdlib.add<td_json_client_execute>("td_json_client_execute");
        tdlib.add<td_json_client_destroy>("td_json_client_destroy");
        return tdlib;
    }
}
