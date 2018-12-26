#include "catch.hpp"

#include <phpcpp.h>
#include "../include/TDApi/TDLibParameters.hpp"

SCENARIO( "Check TDLibParameters", "[TDLibParameters]" ) {
    GIVEN ( "new TDLibParameters" ) {
        auto parameters = new TDLibParameters();

        THEN( "constants exist" ) {
            REQUIRE( ((char*)parameters->USE_TEST_DC) == "use_test_dc" );
            REQUIRE( ((char*)parameters->DATABASE_DIRECOTRY) == "database_directory" );
            REQUIRE( ((char*)parameters->FILES_DIRECTORY) == "files_directory" );
            REQUIRE( ((char*)parameters->USE_FILE_DATABASE) == "use_file_database" );
            REQUIRE( ((char*)parameters->USE_CHAT_INFO_DATABASE) == "use_chat_info_database" );
            REQUIRE( ((char*)parameters->USE_MESSAGE_DATABASE) == "use_message_database" );
            REQUIRE( ((char*)parameters->USE_SECRET_CHATS) == "use_secret_chats" );
            REQUIRE( ((char*)parameters->API_ID) == "api_id" );
            REQUIRE( ((char*)parameters->API_HASH) == "api_hash" );
            REQUIRE( ((char*)parameters->SYSTEM_LANGUAGE_CODE) == "system_language_code" );
            REQUIRE( ((char*)parameters->DEVICE_MODEL) == "device_model" );
            REQUIRE( ((char*)parameters->SYSTEM_VERSION) == "system_version" );
            REQUIRE( ((char*)parameters->APPLICATION_VERSION) == "application_version" );
            REQUIRE( ((char*)parameters->ENABLE_STORAGE_OPTIMIZER) == "enable_storage_optimizer" );
        }

        WHEN ( "set integer parameter" ) {
            Php::Value parameterValue = 11223344;
            parameters->setParameter(TDLibParameters::API_ID, &parameterValue);
            THEN ( "should be the same" ) {
                nlohmann::json parametersArray = parameters->getParameters();
                REQUIRE ( ((int)parametersArray[TDLibParameters::API_ID]) == (int)parameterValue );
            }
        }

        WHEN ( "set parameter of invalid type" ) {
            Php::Value parameterValue = 11223344;
            THEN ( "should throw exception" ) {
                REQUIRE_THROWS( parameters->setParameter(TDLibParameters::API_HASH, &parameterValue) );
            }
        }
    }
}
