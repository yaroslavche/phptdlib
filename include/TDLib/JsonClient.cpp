#include <iostream>

#include <phpcpp.h>

#include "JsonClient.hpp"

#include "../TDApi/TDLibParameters.hpp"

Php::Value JsonClient::query(Php::Parameters &params)
{
    const char *queryParam = params[0];
    double timeout = params[1];
    std::string result = query(queryParam, timeout);
    return result;
}

std::string JsonClient::query(const char *query, double timeout)
{
    BaseJsonClient::send(query);
    std::string result;
    while(true)
    {
        result = BaseJsonClient::receive(timeout);
        if (!result.empty()) {
            break;
        }
    }
    // Php::out << "query: " << query << ", timeout: " << timeout << std::endl << "result: " << result << std::endl << std::endl << std::flush;
    return result;
}

Php::Value JsonClient::setTdlibParameters(Php::Parameters &params)
{
    Php::Value tdlibParams = params[0];
    if(!tdlibParams.instanceOf("TDApi\\TDLibParameters")) throw Php::Exception("First parameter must be instance of TDApi\\TDLibParameters.");
    TDLibParameters *parameters = (TDLibParameters *)tdlibParams.implementation();
    std::string parametersJsonQuery = parameters->toJsonQuery();
    std::string result = query(parametersJsonQuery.c_str(), defaultTimeout);
    return result;
}

Php::Value JsonClient::setDatabaseEncryptionKey(Php::Parameters &params)
{
    const char *new_encryption_key = !params.empty() ? params[0] : "";
    // const char *jsonQuery = "{\"@type\":\"setDatabaseEncryptionKey\"" + (strlen(new_encryption_key) > 0 ? "" : "") + "}"; // todo: how to set new key?
    const char *jsonQuery = "{\"@type\":\"setDatabaseEncryptionKey\"}";
    std::string result = query(jsonQuery, defaultTimeout);
    return result;
}

Php::Value JsonClient::getAuthorizationState(Php::Parameters &params)
{
    // double extra = params[0];
    const char *jsonQuery = "{\"@type\":\"getAuthorizationState\",\"@extra\":0.1234}";
    std::string result = query(jsonQuery, defaultTimeout);
    return result;
}

Php::Value JsonClient::updateAuthorizationState()
{
    const char *jsonQuery = "{\"@type\":\"updateAuthorizationState\"}";
    std::string result = query(jsonQuery, defaultTimeout);
    return result;
}

Php::Value JsonClient::updateOption(Php::Parameters &params)
{
    std::string name = params[0];
    std::string value = params[1];
    std::string jsonQuery = "{\"@type\":\"updateOption\", \"parameters\":{\"" + name + "\":\"" + value + "\"}}";
    std::string result = query(jsonQuery.c_str(), defaultTimeout);
    return result;
}

Php::Value JsonClient::setAuthenticationPhoneNumber(Php::Parameters &params)
{
    std::string phone_number = params[0];
    std::string jsonQuery = "{\"@type\":\"setAuthenticationPhoneNumber\",\"parameters\":{\"phone_number\":\"" + phone_number + "\"}}";
    std::string result = query(jsonQuery.c_str(), defaultTimeout);
    return result;
}
