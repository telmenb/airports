#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "flight_graph.hpp"
#include "airport.hpp"

// Graph Constructor Tests
TEST_CASE("test_get_airport", "[constructor]") {
    FlightGraph fgraph("data/test_airport_data.dat", "test");

    Airport* airport1 = fgraph.GetAirport("GKA");
    Airport* airport3 = fgraph.GetAirport("HGU");
    Airport* airport8 = fgraph.GetAirport("GOH");
    Airport* airport10 = fgraph.GetAirport("THU");

    REQUIRE(airport1 != NULL);
    REQUIRE(airport3 != NULL);
    REQUIRE(airport8 != NULL);
    REQUIRE(airport10 != NULL);

    Airport* not_exist1 = fgraph.GetAirport("LMAO");
    Airport* not_exist2 = fgraph.GetAirport("Two words");
    
    REQUIRE(not_exist1 == NULL);
    REQUIRE(not_exist2 == NULL);
}

TEST_CASE("skip_no_iata", "[constructor]") {
    FlightGraph fgraph("data/test_airport_data.dat", "test");

    REQUIRE(fgraph.MapSize() == 9);
}

TEST_CASE("right_airport_values", "[constructor]") {
    FlightGraph fgraph("data/test_airport_data.dat", "test");

    Airport* airport1 = fgraph.GetAirport("GKA");
    REQUIRE(airport1->iata == "GKA");
    REQUIRE(airport1->name == "Goroka Airport");
    REQUIRE(airport1->country == "Papua New Guinea");
    REQUIRE(airport1->latitude == "-6.081689834590001");
    REQUIRE(airport1->longitude == "145.391998291");

    Airport* airport5 = fgraph.GetAirport("POM");
    REQUIRE(airport5->iata == "POM");
    REQUIRE(airport5->name == "Port Moresby Jacksons International Airport");
    REQUIRE(airport5->country == "Papua New Guinea");
    REQUIRE(airport5->latitude == "-9.443380355834961");
    REQUIRE(airport5->longitude == "147.22000122070312");
}