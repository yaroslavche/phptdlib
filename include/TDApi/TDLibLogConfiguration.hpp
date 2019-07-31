#ifndef TD_API_LOGCONFIGURATION_H
#define TD_API_LOGCONFIGURATION_H

#include <phpcpp.h>

class TDLibLogConfiguration : public Php::Base // namespace: TDApi
{
public:
    static constexpr const int LVL_FATAL_ERROR = 0;
    static constexpr const int LVL_ERROR = 1;
    static constexpr const int LVL_WARNING = 2;
    static constexpr const int LVL_INFO = 3;
    static constexpr const int LVL_DEBUG = 4;
    static constexpr const int LVL_VERBOSE_DEBUG = 5;
    static constexpr const int LVL_ALL = 1024;

    TDLibLogConfiguration() = default;

    virtual ~TDLibLogConfiguration() = default;

    static Php::Value setLogFilePath(Php::Parameters &params);

    static void setLogMaxFileSize(Php::Parameters &params);

    static void setLogVerbosityLevel(Php::Parameters &params);

    static void setLogVerbosityLevel(int logVerbosityLevel);
//    todo: void setLogFatalErrorCallback(Php::Parameters &params);
};

#endif // TD_API_LOGCONFIGURATION_H
