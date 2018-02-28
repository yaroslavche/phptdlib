#include <iostream>

#include <phpcpp.h>

#include <td/telegram/tdjson_export.h>
#include <td/telegram/td_json_client.h>
#include <td/telegram/Log.h>

#include "lib/tdlib_json_client.cpp"
#include "lib/tdlib_json_client_func.cpp"

extern "C" {

PHPCPP_EXPORT void *get_module()
{
    static Php::Extension tdlib("tdlib", "0.0.5");

    // td_json_client class implementation
    Php::Class<TDLibJsonClient> td_json_client("TDLibJsonClient");
    td_json_client.method<&TDLibJsonClient::create> ("create");
    td_json_client.method<&TDLibJsonClient::destroy> ("destroy");
    td_json_client.method<&TDLibJsonClient::execute> ("execute", {
        Php::ByVal("query", Php::Type::String)
    });
    td_json_client.method<&TDLibJsonClient::send> ("send", {
        Php::ByVal("query", Php::Type::String),
    });
    td_json_client.method<&TDLibJsonClient::receive> ("receive", {
        Php::ByVal("timeout", Php::Type::Numeric)
    });
    td_json_client.method<&TDLibJsonClient::sendAndWait> ("sendAndWait", {
        Php::ByVal("query", Php::Type::String),
        Php::ByVal("timeout", Php::Type::Numeric),
    });
    tdlib.add(std::move(td_json_client));

    // tdlib_json_client functions
    tdlib.add<tdlib_td_json_client_create>("td_json_client_create", {
        Php::ByVal("client", Php::Type::Object)
    });
    tdlib.add<tdlib_td_json_client_destroy>("td_json_client_destroy");
    tdlib.add<tdlib_td_json_client_execute>("td_json_client_execute", {
        Php::ByVal("client", Php::Type::Object),
        Php::ByVal("query", Php::Type::String)
    });
    tdlib.add<tdlib_td_json_client_send>("td_json_client_send", {
        Php::ByVal("client", Php::Type::Object),
        Php::ByVal("query", Php::Type::String),
    });
    tdlib.add<tdlib_td_json_client_receive>("td_json_client_receive", {
        Php::ByVal("client", Php::Type::Object),
        Php::ByVal("timeout", Php::Type::Numeric)
    });
    tdlib.add<tdlib_td_json_client_send_and_wait>("td_json_client_send_and_wait", {
        Php::ByVal("client", Php::Type::Object),
        Php::ByVal("query", Php::Type::String),
        Php::ByVal("timeout", Php::Type::Numeric),
    });

    return tdlib;
}
}
