#include <iostream>

#include <phpcpp.h>

#include "TDLibParameters.hpp"

void TDLibParameters::setParameter(Php::Parameters &params)
{
    std::string parameter = params[0];
    Php::Value value = params[1];
    Php::out << "setParameter name: " << parameter << ", value: " << value << ", type: " << value.type() << std::endl << std::flush;
}
