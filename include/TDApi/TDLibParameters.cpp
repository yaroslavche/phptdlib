#include <iostream>
#include <sstream>

#include <phpcpp.h>

#include "TDLibParameters.hpp"

TDLibParameters::TDLibParameters()
{
    parameters["use_test_dc"] = false;
    parameters["database_directory"] = "/var/tmp/tdlib";
    parameters["files_directory"] = "/var/tmp/tdlib";
    parameters["use_file_database"] = false;
    parameters["use_chat_info_database"] = false;
    parameters["use_message_database"] = false;
    parameters["use_secret_chats"] = false;
    parameters["api_id"] = "111111";
    parameters["api_hash"] = "abc123";
    parameters["system_language_code"] = "en";
    parameters["device_model"] = "";
    parameters["system_version"] = "";
    parameters["application_version"] = "0.0.7";
    parameters["enable_storage_optimizer"] = true;
    parameters["ignore_file_names"] = false;
}

Php::Value TDLibParameters::setParameter(Php::Parameters &params)
{
    std::string parameter = params[0];
    Php::Value value = params[1];
    parameters[parameter] = value;
    return this;
}

std::string TDLibParameters::toJsonQuery()
{
    std::string extra=this->extraParameterValue;
    // ugly, i know. You can PR with a better solution =)
    std::string parametersJsonQuery = "{\"@type\":\"setTdlibParameters\","
        "\"@extra\":\""+ extra +"\","
        "\"parameters\":{"
        "\"use_test_dc\":" + getParameterValue("use_test_dc") + ","
        "\"database_directory\":\"" + getParameterValue("database_directory") + "\","
        "\"files_directory\":\"" + getParameterValue("files_directory") + "\","
        "\"use_file_database\":" + getParameterValue("use_file_database") + ","
        "\"use_chat_info_database\":" + getParameterValue("use_chat_info_database") + ","
        "\"use_message_database\":" + getParameterValue("use_message_database") + ","
        "\"use_secret_chats\":" + getParameterValue("use_secret_chats") + ","
        "\"api_id\":\"" + getParameterValue("api_id") + "\","
        "\"api_hash\":\"" + getParameterValue("api_hash") + "\","
        "\"system_language_code\":\"" + getParameterValue("system_language_code") + "\","
        "\"device_model\":\"" + getParameterValue("device_model") + "\","
        "\"system_version\":\"" + getParameterValue("system_version") + "\","
        "\"application_version\":\"" + getParameterValue("application_version") + "\","
        "\"enable_storage_optimizer\":" + getParameterValue("enable_storage_optimizer") + ","
        "\"ignore_file_names\":" + getParameterValue("ignore_file_names") + "}}";
    return parametersJsonQuery;
}

std::string TDLibParameters::getParameterValue(const char *parameter)
{
    std::string value = parameters[parameter];
    if(value == "") return "false"; // can be empty string!!! check if rawValue is bool
    if(value == "1") return "true";
    return value;
}
