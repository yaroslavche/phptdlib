#ifndef TD_API_LOGCONFIGURATION_H
#define TD_API_LOGCONFIGURATION_H

class TDLibLogConfiguration : public Php::Base // namespace: TDApi
{
    public:
    TDLibLogConfiguration() = default;
        virtual ~TDLibLogConfiguration() = default;

        static Php::Value setLogFilePath(Php::Parameters &params);
        static void setLogMaxFileSize(Php::Parameters &params);
        static void setLogVerbosityLevel(Php::Parameters &params);
//    todo: void setLogFatalErrorCallback(Php::Parameters &params);
};

#endif // TD_API_LOGCONFIGURATION_H
