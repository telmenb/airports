#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "flight_graph.hpp"
#include "airport.hpp"

// Graph Constructor Tests
TEST_CASE("test_get_airport", "[constructor]") {
    FlightGraph fgraph("data/test_airport.dat", "test");

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
    FlightGraph fgraph("data/test_airport.dat", "test");

    REQUIRE(fgraph.MapSize() == 9);
}

TEST_CASE("right_airport_values", "[constructor]") {
    FlightGraph fgraph("data/test_airport.dat", "test");

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

TEST_CASE("haversine_distance", "[constructor]") {
    // https://www.movable-type.co.uk/scripts/latlong.html
    REQUIRE(CalculateDistance(-6.081689834590001, 145.391998291, -5.20707988739, 145.789001465) == 106);
}

TEST_CASE("right_destinations", "[constructor]") {
    FlightGraph fgraph("data/test_airport.dat", "data/test_routes.dat");

    Airport* airport4 = fgraph.GetAirport("LAE");
    REQUIRE(airport4->destinations.size() == 3);
    REQUIRE(airport4->destinations.at(0).first == fgraph.GetAirport("GKA"));
    REQUIRE(airport4->destinations.at(0).second == 157);
}

TEST_CASE("skip_duplicate_routes", "[constructor]") {
    FlightGraph fgraph("data/test_airport.dat", "data/test_routes.dat");

    Airport* airport8 = fgraph.GetAirport("GOH");
    REQUIRE(airport8->destinations.size() == 2);
}

TEST_CASE("copy_constructor", "[copy]"){
    FlightGraph fgraph("data/test_airport.dat", "data/test_routes.dat");
    FlightGraph fg1(fgraph);

    REQUIRE_FALSE(fgraph.GetAirport("GKA") == fg1.GetAirport("GKA"));
}

TEST_CASE("assignment", "[copy]"){
    FlightGraph fgraph("data/test_airport.dat", "data/test_routes.dat");
    FlightGraph fg2 = fgraph;

    REQUIRE_FALSE(fgraph.GetAirport("GKA") == fg2.GetAirport("GKA"));
}

TEST_CASE("assignment_2", "[copy]"){
    FlightGraph fgraph("data/test_airport.dat", "data/test_routes.dat");
    FlightGraph fg2("data/airports.dat", "data/routes.dat");

    REQUIRE_FALSE(fgraph.MapSize() == fg2.MapSize());

    fg2 = fgraph;

    REQUIRE_FALSE(fgraph.GetAirport("GKA") == fg2.GetAirport("GKA"));
    REQUIRE(fgraph.MapSize() == fg2.MapSize());
}