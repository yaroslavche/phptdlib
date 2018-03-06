#ifndef TD_API_TDLIBPARAMETERS_H
#define TD_API_TDLIBPARAMETERS_H

class TDLibParameters : public Php::Base // namespace: TDApi
{
    private:
        std::vector<Php::Value> tdlibParams;
    //     bool locked = false;

    public:
        TDLibParameters() = default;
        virtual ~TDLibParameters() = default;

        // void __construct(array);

        Php::Value setParameter(Php::Parameters &params);
        const char *toJson();

        // inline void setLocked() { locked == true; }
        // can set parameters if locked == false

        // check input
        // Php::Value use_test_dc = true;
        // "use_test_dc" => true,
        // "database_directory" => "/var/tmp/tdlib",
        // "files_directory" => "/var/tmp/tdlib",
        // "use_file_database" => false,
        // "use_chat_info_database" => false,
        // "use_message_database" => false,
        // "use_secret_chats" => false,
        // "api_id" => 111111,
        // "api_hash" => "a1b2c3",
        // "system_language_code" => "en",
        // "device_model" => php_uname('s'),
        // "system_version" => php_uname('v'),
        // "application_version" => "0.0.4",
        // "enable_storage_optimizer" => true,
        // "ignore_file_names" => false

};

#endif // TD_API_TDLIBPARAMETERS_H
