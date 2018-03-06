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
    Php::out << "query: " << query << ", timeout: " << timeout << std::endl << "result: " << result << std::endl << std::flush;
    return result;
}

Php::Value JsonClient::setTdlibParameters(Php::Parameters &params)
{
    Php::Value tdlibParams = params[0];
    if(!tdlibParams.instanceOf("TDApi\\TDLibParameters")) throw Php::Exception("First parameter must be instance of TDApi\\TDLibParameters.");
    TDLibParameters *parameters = (TDLibParameters *)tdlibParams.implementation();
    std::string result = query(parameters->toJson(), 10);
    return result;
}
Php::Value JsonClient::setDatabaseEncryptionKey(Php::Parameters &params)
{
    Php::out << "setDatabaseEncryptionKey: " << params[0] << std::endl << std::flush;
    // if(new_encryption_key !== nullptr);
    std::string result = query("{\"@type\":\"setDatabaseEncryptionKey\"}", 10);
    return result;
}

Php::Value JsonClient::getAuthorizationState(Php::Parameters &params)
{
    double extra = params[0];
    // if(new_encryption_key !== nullptr);
    std::string result = query("{\"@type\":\"getAuthorizationState\",\"@extra\":0.1234}", 10);
    return result;
}
