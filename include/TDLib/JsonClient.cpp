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
    int i = 1;
    try
    {
        while(true)
        {
            result = BaseJsonClient::receive(1);
            if (!result.empty()) {
                if (result == "{\"@type\":\"ok\",\"@extra\":null}") break;
                if (result.find("{\"@type\":\"error\"") != std::string::npos) break;
                if (result.find("{\"@type\":\"authorizationStateWait") == 0) break;
            }
            i++;
        }
    }
    catch(...)
    {
        Php::out << "EXCEPTION" << std::endl << std::endl;
    }
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

Php::Value JsonClient::checkDatabaseEncryptionKey(Php::Parameters &params)
{
    const std::string key = params[0];
    const std::string jsonQuery = "{\"@type\":\"checkDatabaseEncryptionKey\", \"key\":\"" + key + "\"}";
    std::string result = query(jsonQuery.c_str(), defaultTimeout);
    return result;
}

Php::Value JsonClient::setDatabaseEncryptionKey(Php::Parameters &params)
{
    const std::string new_encryption_key = !params.empty() ? params[0] : "";
    const std::string jsonQuery = "{\"@type\":\"setDatabaseEncryptionKey\"" + (new_encryption_key.length() > 0 ? ",\"new_encryption_key\":\"" + new_encryption_key + "\"" : "") + "}";
    std::string result = query(jsonQuery.c_str(), defaultTimeout);
    return result;
}

Php::Value JsonClient::getAuthorizationState(Php::Parameters &params)
{
    // double extra = params[0];
    const char *jsonQuery = "{\"@type\":\"getAuthorizationState\",\"@extra\":0.1234}";
    std::string result = query(jsonQuery, defaultTimeout);
    return result;
}

Php::Value JsonClient::setAuthenticationPhoneNumber(Php::Parameters &params)
{
    std::string phone_number = params[0];
    std::string jsonQuery = "{\"@type\":\"setAuthenticationPhoneNumber\", \"phone_number\":\"" + phone_number + "\"}";
    std::string result = query(jsonQuery.c_str(), defaultTimeout);
    return result;
}
