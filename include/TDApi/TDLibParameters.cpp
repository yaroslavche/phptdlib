#include <iostream>
#include <vector>

#include <phpcpp.h>

#include "TDLibParameters.hpp"

Php::Value TDLibParameters::setParameter(Php::Parameters &params)
{
    std::string parameter = params[0];
    Php::Value value = params[1];
    // tdlibParams;
    Php::out << "setParameter name: " << parameter << ", value: " << value << ", type: " << value.type() << std::endl << std::flush;
    return this;
}

const char *TDLibParameters::toJson()
{
    return "{\"@type\":\"setTdlibParameters\", \"parameters\":{\"use_test_dc\":true, \"database_directory\":\"\\/var\\/tmp\\/tdlib\", \"files_directory\":\"\\/var\\/tmp\\/tdlib\", \"use_file_database\":false, \"use_chat_info_database\":false, \"use_message_database\":false, \"use_secret_chats\":false, \"api_id\":111111, \"api_hash\":\"a1b2c3\", \"system_language_code\":\"en\", \"device_model\":\"Linux\", \"system_version\":\"#1 SMP PREEMPT Thu Feb 22 21:48:29 UTC 2018 (52ce732)\", \"application_version\":\"0.0.6\", \"enable_storage_optimizer\":true, \"ignore_file_names\":false}}";
}
