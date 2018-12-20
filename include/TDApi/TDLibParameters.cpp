#include "TDLibParameters.hpp"
#include "../../tdlib.hpp"

TDLibParameters::TDLibParameters()
{
    parameters[USE_TEST_DC] = false;
    parameters[DATABASE_DIRECOTRY] = "/var/tmp/tdlib";
    parameters[FILES_DIRECTORY] = "/var/tmp/tdlib";
    parameters[USE_FILE_DATABASE] = false;
    parameters[USE_CHAT_INFO_DATABASE] = false;
    parameters[USE_MESSAGE_DATABASE] = false;
    parameters[USE_SECRET_CHATS] = false;
    parameters[API_ID] = 0;
    parameters[API_HASH] = "";
    parameters[SYSTEM_LANGUAGE_CODE] = "en";
    parameters[DEVICE_MODEL] = "";
    parameters[SYSTEM_VERSION] = "";
    parameters[APPLICATION_VERSION] = TDLIB_PHP_VERSION;
    parameters[ENABLE_STORAGE_OPTIMIZER] = true;
    parameters[IGNORE_FILE_NAMES] = false;
}

Php::Value TDLibParameters::setParameter(Php::Parameters &params)
{
    std::string parameter = params[0];
    Php::Value value = params[1];

    auto paramsIt = parameters.find(parameter);
    if (paramsIt == parameters.end())
    {
        throw Php::Exception("Invalid parameter name");
    }

    if (value.isNumeric() && paramsIt->is_number())
    {
        int typedValue = value;
        parameters[parameter] = typedValue;
    }
    else if (value.isString() && paramsIt->is_string())
    {
        std::string typedValue = value;
        parameters[parameter] = typedValue;
    }
    else if (value.isBool() && paramsIt->is_boolean())
    {
        bool typedValue = value;
        parameters[parameter] = typedValue;
    }
    else
    {
        throw Php::Exception("Invalid TDLib parameter type");
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
            assert(false);
        }
    }

    result["parameters"] = phpValueParameters;
    return result;
}