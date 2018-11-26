#ifndef TD_API_TDLIBPARAMETERS_H
#define TD_API_TDLIBPARAMETERS_H

#include <nlohmann/json.hpp>

class TDLibParameters : public Php::Base // namespace: TDApi
{
    private:
        nlohmann::json parameters;

    public:
        TDLibParameters();
        virtual ~TDLibParameters() = default;

        Php::Value setParameter(Php::Parameters &params);
        nlohmann::json getParameters();
        Php::Value __debugInfo();

        // inline void setLocked() { locked == true; }
        // can set parameters if locked == false
};

#endif // TD_API_TDLIBPARAMETERS_H
