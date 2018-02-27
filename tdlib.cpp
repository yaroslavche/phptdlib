#include <phpcpp.h>
#include <iostream>
#include <td/telegram/tdjson_export.h>
#include <td/telegram/td_json_client.h>
#include "tdlib_json_client.cpp"

extern "C" {

    PHPCPP_EXPORT void *get_module()
    {
        static Php::Extension tdlib("tdlib", "0.0.3");

        // td_json_client class implementation
        Php::Class<TDLibJsonClient> td_json_client("TDLibJsonClient");
        td_json_client.method<&TDLibJsonClient::create> ("create");
        td_json_client.method<&TDLibJsonClient::destroy> ("destroy");
        td_json_client.method<&TDLibJsonClient::execute> ("execute", {
            Php::ByVal("query", Php::Type::String)
        });
        td_json_client.method<&TDLibJsonClient::send> ("send", {
            Php::ByVal("query", Php::Type::String),
            Php::ByVal("timeout", Php::Type::Numeric, false),
        });
        td_json_client.method<&TDLibJsonClient::receive> ("receive", {
            Php::ByVal("timeout", Php::Type::Numeric)
        });
        tdlib.add(std::move(td_json_client));

        return tdlib;
    }
}
