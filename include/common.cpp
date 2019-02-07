#include "common.hpp"

Php::Value getPhpFunctionArgument(Php::Parameters &params, int parameterIndex)
{
    if (params.size() <= parameterIndex || params[parameterIndex].isNull())
    {
        return nullptr;
    }

    return params[parameterIndex];
}

int getPhpFunctionArgument(Php::Parameters &params, int parameterIndex, int defaultValue)
{
    if (params.size() <= parameterIndex || params[parameterIndex].isNull())
    {
        return defaultValue;
    }

    return params[parameterIndex];
}

std::string getPhpFunctionArgument(Php::Parameters &params, int parameterIndex, std::string defaultValue)
{
    if (params.size() <= parameterIndex || params[parameterIndex].isNull())
    {
        return defaultValue;
    }

    return params[parameterIndex];
}

const char* getPhpFunctionArgument(Php::Parameters &params, int parameterIndex, const char *defaultValue)
{
    if (params.size() <= parameterIndex || params[parameterIndex].isNull())
    {
        return defaultValue;
    }

    return params[parameterIndex];
}

double getPhpFunctionArgument(Php::Parameters &params, int parameterIndex, double defaultValue)
{
    if (params.size() <= parameterIndex || params[parameterIndex].isNull())
    {
        return defaultValue;
    }

    return params[parameterIndex];
}
