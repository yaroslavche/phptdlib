#include <td/telegram/td_log.h>

#include "TDLibLogConfiguration.hpp"
#include "../common.hpp"

Php::Value TDLibLogConfiguration::setLogFilePath(Php::Parameters &params)
{
    return td_set_log_file_path(getPhpFunctionArgument(params, 0, ""));
}

void TDLibLogConfiguration::setLogMaxFileSize(Php::Parameters &params)
{
    td_set_log_max_file_size(getPhpFunctionArgument(params, 0, 0));
}

void TDLibLogConfiguration::setLogVerbosityLevel(Php::Parameters &params)
{
    setLogVerbosityLevel(getPhpFunctionArgument(params, 0, LVL_ERROR));
}

void TDLibLogConfiguration::setLogVerbosityLevel(int logVerbosityLevel)
{
    td_set_log_verbosity_level(logVerbosityLevel);
}
