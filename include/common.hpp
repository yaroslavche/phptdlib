#include <phpcpp.h>

Php::Value getPhpFunctionArgument(Php::Parameters &params, int parameterIndex);

int getPhpFunctionArgument(Php::Parameters &params, int parameterIndex, int defaultValue);
std::string getPhpFunctionArgument(Php::Parameters &params, int parameterIndex, std::string defaultValue);
const char* getPhpFunctionArgument(Php::Parameters &params, int parameterIndex, const char *defaultValue);
double getPhpFunctionArgument(Php::Parameters &params, int parameterIndex, double defaultValue);
