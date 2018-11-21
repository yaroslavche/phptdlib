#include <iostream>

#include <phpcpp.h>

#include <td/telegram/tdjson_export.h>
#include <td/telegram/td_json_client.h>

#include "include/td_json_client_func.cpp"
#include "include/TDLib/JsonClient.hpp"
#include "include/TDApi/TDLibParameters.hpp"
#include "include/TDApi/TDLibLogConfiguration.hpp"

extern "C" {

PHPCPP_EXPORT void *get_module()
{
    static Php::Extension tdlib("tdlib", "0.0.8");


    Php::Namespace TDLibNamespace("TDLib");

    // TDLib\BaseJsonClient
    Php::Class<BaseJsonClient> base_json_client("BaseJsonClient");
    base_json_client.method<&BaseJsonClient::__construct> ("__construct");
    base_json_client.method<&BaseJsonClient::create> ("create");
    base_json_client.method<&BaseJsonClient::destroy> ("destroy");
    base_json_client.method<&BaseJsonClient::execute> ("execute", {
        Php::ByVal("query", Php::Type::String)
    });
    base_json_client.method<&BaseJsonClient::send> ("send", {
        Php::ByVal("query", Php::Type::String)
    });
    base_json_client.method<&BaseJsonClient::receive> ("receive", {
        Php::ByVal("timeout", Php::Type::Numeric)
    });

    TDLibNamespace.add(std::move(base_json_client));


    // TDLib\JsonClient
    Php::Class<JsonClient> json_client("JsonClient");
    json_client.method<&JsonClient::create> ("create");
    json_client.method<&JsonClient::destroy> ("destroy");
    json_client.method<&JsonClient::execute> ("execute", {
        Php::ByVal("query", Php::Type::String)
    });
    json_client.method<&JsonClient::send> ("send", {
        Php::ByVal("query", Php::Type::String)
    });
    json_client.method<&JsonClient::receive> ("receive", {
        Php::ByVal("timeout", Php::Type::Numeric, false)
    });
    json_client.method<&JsonClient::query> ("query", {
        Php::ByVal("query", Php::Type::String),
        Php::ByVal("timeout", Php::Type::Numeric, false)
    });
    json_client.method<&JsonClient::getReceivedResponses> ("getReceivedResponses");

    json_client.method<&JsonClient::setTdlibParameters> ("setTdlibParameters", {
        Php::ByVal("parameters", "TDApi\\TDLibParameters"),
    });
    json_client.method<&JsonClient::setDatabaseEncryptionKey> ("setDatabaseEncryptionKey", {
        Php::ByVal("new_encryption_key", Php::Type::String, false),
    });
    json_client.method<&JsonClient::checkDatabaseEncryptionKey> ("checkDatabaseEncryptionKey", {
        Php::ByVal("key", Php::Type::String),
    });
    json_client.method<&JsonClient::getAuthorizationState> ("getAuthorizationState", {
        Php::ByVal("extra", Php::Type::Float, false),
    });
    json_client.method<&JsonClient::setDefaultTimeout> ("setDefaultTimeout", {
        Php::ByVal("defaultTimeout", Php::Type::Float),
    });
    json_client.method<&JsonClient::setAuthenticationPhoneNumber> ("setAuthenticationPhoneNumber", {
        Php::ByVal("phone_number", Php::Type::String),
    });

    TDLibNamespace.add(std::move(json_client));

    tdlib.add(std::move(TDLibNamespace));





    Php::Namespace TDApiNamespace("TDApi");

    // TDApi\TDLibParameters
    Php::Class<TDLibParameters> td_api_tdlibParameters("TDLibParameters");
    td_api_tdlibParameters.method<&TDLibParameters::setParameter> ("setParameter", {
        Php::ByVal("name", Php::Type::String),
        Php::ByVal("value")
    });

    TDApiNamespace.add(std::move(td_api_tdlibParameters));


    // TDApi\TDLibLogConfiguration
    Php::Class<TDLibLogConfiguration> td_api_logConfiguration("LogConfiguration");
    td_api_logConfiguration.method<&TDLibLogConfiguration::setLogFilePath> ("setLogFilePath", {
        Php::ByVal("logFilePath", Php::Type::String)
    });
    td_api_logConfiguration.method<&TDLibLogConfiguration::setLogMaxFileSize> ("setLogMaxFileSize", {
        Php::ByVal("logMaxFileSize", Php::Type::Numeric)
    });
    td_api_logConfiguration.method<&TDLibLogConfiguration::setLogVerbosityLevel> ("setLogVerbosityLevel", {
        Php::ByVal("logVerbosityLevel", Php::Type::Numeric)
    });

    td_api_logConfiguration.property("LVL_FATAL_ERROR", 0, Php::Const);
    td_api_logConfiguration.property("LVL_ERROR", 1, Php::Const);
    td_api_logConfiguration.property("LVL_WARNING", 2, Php::Const);
    td_api_logConfiguration.property("LVL_INFO", 3, Php::Const);
    td_api_logConfiguration.property("LVL_DEBUG", 4, Php::Const);
    td_api_logConfiguration.property("LVL_VERBOSE_DEBUG", 5, Php::Const);
    td_api_logConfiguration.property("LVL_ALL", 1024, Php::Const);

    TDApiNamespace.add(std::move(td_api_logConfiguration));

    tdlib.add(std::move(TDApiNamespace));



    // td_json_client_*
    tdlib.add<td_json_client_func_create>("td_json_client_create");
    tdlib.add<td_json_client_func_destroy>("td_json_client_destroy", {
        Php::ByVal("client", Php::Type::Object)
    });
    tdlib.add<td_json_client_func_execute>("td_json_client_execute", {
        Php::ByVal("client", Php::Type::Object),
        Php::ByVal("query", Php::Type::String)
    });
    tdlib.add<td_json_client_func_send>("td_json_client_send", {
        Php::ByVal("client", Php::Type::Object),
        Php::ByVal("query", Php::Type::String)
    });
    tdlib.add<td_json_client_func_receive>("td_json_client_receive", {
        Php::ByVal("client", Php::Type::Object),
        Php::ByVal("timeout", Php::Type::Numeric)
    });

    return tdlib;
}
}
