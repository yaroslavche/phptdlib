#include "catch.hpp"

#include "../../include/TDLib/BaseJsonClient.hpp"
#include "../../include/TDLib/JsonClient.hpp"


SCENARIO ("Check base JsonClient methods", "[JsonClient]") {
    GIVEN ("new JsonClient") {
        auto *client = new JsonClient();
        client->create();

        nlohmann::json query;
        query["@type"] = "getAuthorizationState";

        nlohmann::json expectedResponse;
        expectedResponse["@type"] = "authorizationStateWaitTdlibParameters";


        WHEN ("`query` method is called with @extra of type string") {
            nlohmann::json extra = "1234";

            query["@extra"] = extra;
            expectedResponse["@extra"] = extra;

            std::string response = client->query(query.dump().c_str(), 5, &extra);
            nlohmann::json r = nlohmann::json::parse(response);
            THEN ("get correct response by `receive` method") {
                REQUIRE (r == expectedResponse);
            }
        }

        WHEN ("`query` method is called with @extra of type int") {
            nlohmann::json extra = 1234;

            query["@extra"] = extra;
            expectedResponse["@extra"] = extra;

            std::string response = client->query(query.dump().c_str(), 5, &extra);
            nlohmann::json r = nlohmann::json::parse(response);
            THEN ("get correct response by `receive` method") {
                REQUIRE (r == expectedResponse);
            }
        }

        WHEN ("`query` method is called with @extra of type float") {
            nlohmann::json extra = 0.1234;

            query["@extra"] = extra;
            expectedResponse["@extra"] = extra;

            std::string response = client->query(query.dump().c_str(), 5, &extra);
            nlohmann::json r = nlohmann::json::parse(response);
            THEN ("get correct response by `receive` method") {
                REQUIRE (r == expectedResponse);
            }
        }

        WHEN ("`query` method is called without @extra") {
            std::string response = client->addExtraAndSendQuery((std::string)(query["@type"]), &query, 5);
            nlohmann::json r = nlohmann::json::parse(response);
            r.erase("@extra");
            THEN ("get correct response by `receive` method") {
                REQUIRE (r == expectedResponse);
            }
        }
    }
}