#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// Test for test
TEST_CASE("Sanity", "[tag]") {
    REQUIRE(1 == true);
}