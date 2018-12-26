#ifndef TD_API_TDLIBPARAMETERS_H
#define TD_API_TDLIBPARAMETERS_H

#include <nlohmann/json.hpp>
#include <phpcpp.h>

class TDLibParameters : public Php::Base // namespace: TDApi
{
    private:
        nlohmann::json parameters;

    public:
        static constexpr const char* USE_TEST_DC = "use_test_dc";
        static constexpr const char* DATABASE_DIRECOTRY = "database_directory";
        static constexpr const char* FILES_DIRECTORY = "files_directory";
        static constexpr const char* USE_FILE_DATABASE = "use_file_database";
        static constexpr const char* USE_CHAT_INFO_DATABASE = "use_chat_info_database";
        static constexpr const char* USE_MESSAGE_DATABASE = "use_message_database";
        static constexpr const char* USE_SECRET_CHATS = "use_secret_chats";
        static constexpr const char* API_ID = "api_id";
        static constexpr const char* API_HASH = "api_hash";
        static constexpr const char* SYSTEM_LANGUAGE_CODE = "system_language_code";
        static constexpr const char* DEVICE_MODEL = "device_model";
        static constexpr const char* SYSTEM_VERSION = "system_version";
        static constexpr const char* APPLICATION_VERSION = "application_version";
        static constexpr const char* ENABLE_STORAGE_OPTIMIZER = "enable_storage_optimizer";
        static constexpr const char* IGNORE_FILE_NAMES = "ignore_file_names";

        TDLibParameters();
        virtual ~TDLibParameters() = default;

        Php::Value setParameter(Php::Parameters &params);
        void setParameter(const std::string &parameterName, Php::Value *parameterValue);
        void setParameter(const std::string &parameterName, int parameterValue);
        void setParameter(const std::string &parameterName, std::string parameterValue);
        void setParameter(const std::string &parameterName, bool parameterValue);
        nlohmann::json getParameters();
        Php::Value __debugInfo();

        // inline void setLocked() { locked == true; }
        // can set parameters if locked == false
};

#endif // TD_API_TDLIBPARAMETERS_H
