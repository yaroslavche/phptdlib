#include "catch.hpp"
#include "../../include/TDApi/TDLibLogConfiguration.hpp"

TEST_CASE( "Check TDLibLogConfiguration", "[TDLibLogConfiguration]" ) {
    SECTION ( "checking constants" ) {
        REQUIRE ( ((int)TDLibLogConfiguration::LVL_FATAL_ERROR) == 0 );
        REQUIRE ( ((int)TDLibLogConfiguration::LVL_ERROR) == 1 );
        REQUIRE ( ((int)TDLibLogConfiguration::LVL_WARNING) == 2 );
        REQUIRE ( ((int)TDLibLogConfiguration::LVL_INFO) == 3 );
        REQUIRE ( ((int)TDLibLogConfiguration::LVL_DEBUG) == 4 );
        REQUIRE ( ((int)TDLibLogConfiguration::LVL_VERBOSE_DEBUG) == 5 );
        REQUIRE ( ((int)TDLibLogConfiguration::LVL_ALL) == 1024 );
    }

    SECTION ( "setting loglevel to LVL_FATAL_ERROR" ) {
        TDLibLogConfiguration::setLogVerbosityLevel(TDLibLogConfiguration::LVL_FATAL_ERROR);
    }
}
