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
    parameters["api_id"] = 0;
    parameters["api_hash"] = "";
    parameters["system_language_code"] = "en";
    parameters["device_model"] = "";
    parameters["system_version"] = "";
    parameters["application_version"] = "0.0.1";
    parameters["enable_storage_optimizer"] = true;
    parameters["ignore_file_names"] = false;
}

Php::Value TDLibParameters::setParameter(Php::Parameters &params)
{
    std::string parameter = params[0];
    Php::Value value = params[1];

    if (value.isNumeric())
    {
        int typedValue = value;
        parameters[parameter] = typedValue;
    }
    else if (value.isString())
    {
        std::string typedValue = value;
        parameters[parameter] = typedValue;
    }
    else if (value.isBool())
    {
        bool typedValue = value;
        parameters[parameter] = typedValue;
    }
    else
    {
        throw Php::Exception("TDLib parameter could be string, number or bool only");
    }
    return this;
}

nlohmann::json TDLibParameters::getParameters()
{
    return parameters;
}

Php::Value TDLibParameters::__debugInfo()
{
    Php::Value phpValueParameters, result;

    for (auto iterator=parameters.begin(); iterator != parameters.end(); iterator++) {
        if ((*iterator).is_number())
        {
            int value = iterator.value();
            phpValueParameters[iterator.key()] = value;
        }
        else if ((*iterator).is_string())
        {
            std::string value = iterator.value();
            phpValueParameters[iterator.key()] = value;
        }
        else if ((*iterator).is_boolean())
        {
            bool value = iterator.value();
            phpValueParameters[iterator.key()] = value;
        }
        else if ((*iterator).is_null())
        {
            phpValueParameters[iterator.key()] = nullptr;
        }
        else {
            throw Php::Exception("Invalid TDLib parameter value");
        }
    }

    result["parameters"] = phpValueParameters;
    return result;
}