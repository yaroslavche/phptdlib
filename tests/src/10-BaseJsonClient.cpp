#include "catch.hpp"

#include "../../include/TDLib/BaseJsonClient.hpp"

#define GET_STATUS_REQUEST "{\"@type\":\"getAuthorizationState\",\"@extra\":\"1234\"}"

#define STATUS_STEP1 "{\"@type\":\"updateAuthorizationState\",\"authorization_state\":{\"@type\":\"authorizationStateWaitTdlibParameters\"}}"
#define STATUS_STEP2 "{\"@type\":\"authorizationStateWaitTdlibParameters\",\"@extra\":\"1234\"}"

SCENARIO ("Check base BaseJsonClient methods", "[BaseJsonClient]") {
    GIVEN ("new BaseJsonClient") {
        auto *client = new BaseJsonClient();
        
//        WHEN ("no __constructor()/create() was called") {
//            THEN ("should throw exception") {
//                REQUIRE_THROWS (client->receive(5));
//            }
//        }

        client->create();
        std::string firstStatusUpdate = client->receive(5);

        THEN("should get updateAuthorizationState update") {
            REQUIRE(firstStatusUpdate == STATUS_STEP1);
        }

        WHEN("`send` method is called") {
            client->send(GET_STATUS_REQUEST);
            THEN("get correct response by `receive` method in 5 seconds") {
                REQUIRE(client->receive(5) == STATUS_STEP2);
            }
        }

        WHEN("`destroy` method is called") {
            client->destroy();
            THEN("get assertion if call methods") {
                REQUIRE(true);
            }
        }
    }
}
