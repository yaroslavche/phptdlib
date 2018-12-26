#include <td/telegram/td_log.h>

#include "TDLibLogConfiguration.hpp"

Php::Value TDLibLogConfiguration::setLogFilePath(Php::Parameters &params)
{
    return td_set_log_file_path(params[0]);
}

void TDLibLogConfiguration::setLogMaxFileSize(Php::Parameters &params)
{
    int maxLogFileSize=params[0];
    td_set_log_max_file_size(maxLogFileSize);
}

void TDLibLogConfiguration::setLogVerbosityLevel(Php::Parameters &params)
{
    int logVerbosityLevel=params[0];
    setLogVerbosityLevel(logVerbosityLevel);
}

void TDLibLogConfiguration::setLogVerbosityLevel(int logVerbosityLevel)
{
    td_set_log_verbosity_level(logVerbosityLevel);
}
