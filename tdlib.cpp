#include <iostream>

#include <phpcpp.h>

#include <td/telegram/tdjson_export.h>
#include <td/telegram/td_json_client.h>

#include "tdlib.hpp"

#include "include/td_json_client_func.hpp"
#include "include/TDLib/JsonClient.hpp"
#include "include/TDApi/TDLibParameters.hpp"
#include "include/TDApi/TDLibLogConfiguration.hpp"

extern "C" {

PHPCPP_EXPORT void *get_module() {
    static Php::Extension tdlib("tdlib", TDLIB_PHP_VERSION);


    Php::Namespace TDLibNamespace("TDLib");

    // TDLib\BaseJsonClient
    Php::Class<BaseJsonClient> base_json_client("BaseJsonClient");
    base_json_client.method<&BaseJsonClient::__construct>("__construct");
    base_json_client.method<&BaseJsonClient::__destruct>("__destruct");
    base_json_client.method<&BaseJsonClient::execute>("execute", {
            Php::ByVal("query", Php::Type::String)
    });
    base_json_client.method<&BaseJsonClient::send>("send", {
            Php::ByVal("query", Php::Type::String)
    });
    base_json_client.method<&BaseJsonClient::receive>("receive", {
            Php::ByVal("timeout", Php::Type::Numeric)
    });

    TDLibNamespace.add(std::move(base_json_client));


    // TDLib\JsonClient
    Php::Class<JsonClient> json_client("JsonClient");
    // BaseJsonClient
    json_client.method<&JsonClient::__construct>("__construct");
    json_client.method<&JsonClient::__destruct>("__destruct");
    json_client.method<&JsonClient::execute>("execute", {
            Php::ByVal("query", Php::Type::String)
    });
    json_client.method<&JsonClient::send>("send", {
            Php::ByVal("query", Php::Type::String)
    });
    json_client.method<&JsonClient::receive>("receive", {
            Php::ByVal("timeout", Php::Type::Numeric, false)
    });
    // JsonClient
    json_client.method<&JsonClient::query>("query", {
            Php::ByVal("query", Php::Type::String),
            Php::ByVal("timeout", Php::Type::Numeric, false)
    });
    json_client.method<&JsonClient::getReceivedResponses>("getReceivedResponses");
    json_client.method<&JsonClient::setDefaultTimeout>("setDefaultTimeout", {
            Php::ByVal("defaultTimeout", Php::Type::Float),
    });
    // tdlib Function Class Reference
    json_client.method<&JsonClient::checkDatabaseEncryptionKey>("checkDatabaseEncryptionKey", {
            Php::ByVal("key", Php::Type::String),
            Php::ByVal("timeout", Php::Type::Float, false)
    });
    json_client.method<&JsonClient::getAuthorizationState>("getAuthorizationState", {
            Php::ByVal("timeout", Php::Type::Float, false)
    });
    json_client.method<&JsonClient::setAuthenticationPhoneNumber>("setAuthenticationPhoneNumber", {
            Php::ByVal("phone_number", Php::Type::String),
            Php::ByVal("timeout", Php::Type::Float, false)
    });
    json_client.method<&JsonClient::setDatabaseEncryptionKey>("setDatabaseEncryptionKey", {
            Php::ByVal("new_encryption_key", Php::Type::String, false),
            Php::ByVal("timeout", Php::Type::Float, false)
    });
    json_client.method<&JsonClient::setTdlibParameters>("setTdlibParameters", {
            Php::ByVal("parameters", "TDApi\\TDLibParameters"),
            Php::ByVal("timeout", Php::Type::Float, false)
    });

    TDLibNamespace.add(std::move(json_client));

    tdlib.add(std::move(TDLibNamespace));


    Php::Namespace TDApiNamespace("TDApi");

    // TDApi\TDLibParameters
    Php::Class<TDLibParameters> td_api_tdlibParameters("TDLibParameters");
    td_api_tdlibParameters.method<&TDLibParameters::setParameter>("setParameter", {
            Php::ByVal("name", Php::Type::String),
            Php::ByVal("value")
    });
    td_api_tdlibParameters.method<&TDLibParameters::__debugInfo>("__debugInfo");

    td_api_tdlibParameters.property("USE_TEST_DC", TDLibParameters::USE_TEST_DC, Php::Const);
    td_api_tdlibParameters.property("DATABASE_DIRECTORY", TDLibParameters::DATABASE_DIRECTORY, Php::Const);
    td_api_tdlibParameters.property("FILES_DIRECTORY", TDLibParameters::FILES_DIRECTORY, Php::Const);
    td_api_tdlibParameters.property("USE_FILE_DATABASE", TDLibParameters::USE_FILE_DATABASE, Php::Const);
    td_api_tdlibParameters.property("USE_CHAT_INFO_DATABASE", TDLibParameters::USE_CHAT_INFO_DATABASE, Php::Const);
    td_api_tdlibParameters.property("USE_MESSAGE_DATABASE", TDLibParameters::USE_MESSAGE_DATABASE, Php::Const);
    td_api_tdlibParameters.property("USE_SECRET_CHATS", TDLibParameters::USE_SECRET_CHATS, Php::Const);
    td_api_tdlibParameters.property("API_ID", TDLibParameters::API_ID, Php::Const);
    td_api_tdlibParameters.property("API_HASH", TDLibParameters::API_HASH, Php::Const);
    td_api_tdlibParameters.property("SYSTEM_LANGUAGE_CODE", TDLibParameters::SYSTEM_LANGUAGE_CODE, Php::Const);
    td_api_tdlibParameters.property("DEVICE_MODEL", TDLibParameters::DEVICE_MODEL, Php::Const);
    td_api_tdlibParameters.property("SYSTEM_VERSION", TDLibParameters::SYSTEM_VERSION, Php::Const);
    td_api_tdlibParameters.property("APPLICATION_VERSION", TDLibParameters::APPLICATION_VERSION, Php::Const);
    td_api_tdlibParameters.property("ENABLE_STORAGE_OPTIMIZER", TDLibParameters::ENABLE_STORAGE_OPTIMIZER, Php::Const);
    td_api_tdlibParameters.property("IGNORE_FILE_NAMES", TDLibParameters::IGNORE_FILE_NAMES, Php::Const);

    TDApiNamespace.add(std::move(td_api_tdlibParameters));


    // TDApi\TDLibLogConfiguration
    Php::Class<TDLibLogConfiguration> td_api_logConfiguration("LogConfiguration");
    td_api_logConfiguration.method<&TDLibLogConfiguration::setLogFilePath>("setLogFilePath", {
            Php::ByVal("logFilePath", Php::Type::String)
    });
    td_api_logConfiguration.method<&TDLibLogConfiguration::setLogMaxFileSize>("setLogMaxFileSize", {
            Php::ByVal("logMaxFileSize", Php::Type::Numeric)
    });
    td_api_logConfiguration.method<&TDLibLogConfiguration::setLogVerbosityLevel>("setLogVerbosityLevel", {
            Php::ByVal("logVerbosityLevel", Php::Type::Numeric)
    });

    td_api_logConfiguration.property("LVL_FATAL_ERROR", TDLibLogConfiguration::LVL_FATAL_ERROR, Php::Const);
    td_api_logConfiguration.property("LVL_ERROR", TDLibLogConfiguration::LVL_ERROR, Php::Const);
    td_api_logConfiguration.property("LVL_WARNING", TDLibLogConfiguration::LVL_WARNING, Php::Const);
    td_api_logConfiguration.property("LVL_INFO", TDLibLogConfiguration::LVL_INFO, Php::Const);
    td_api_logConfiguration.property("LVL_DEBUG", TDLibLogConfiguration::LVL_DEBUG, Php::Const);
    td_api_logConfiguration.property("LVL_VERBOSE_DEBUG", TDLibLogConfiguration::LVL_VERBOSE_DEBUG, Php::Const);
    td_api_logConfiguration.property("LVL_ALL", TDLibLogConfiguration::LVL_ALL, Php::Const);

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
