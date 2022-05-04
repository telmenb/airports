#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <fstream>
#include "flight_graph.hpp"
#include "airport.hpp"
#include "heap.hpp"

// Graph Constructor Tests
TEST_CASE("test_get_airport", "[constructor]") {
    FlightGraph fgraph("data/test_airports.dat", "test");

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
    FlightGraph fgraph("data/test_airports.dat", "test");

    REQUIRE(fgraph.MapSize() == 9);
}

TEST_CASE("right_airport_values", "[constructor]") {
    FlightGraph fgraph("data/test_airports.dat", "test");

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
    FlightGraph fgraph("data/test_airports.dat", "data/test_routes.dat");

    Airport* airport4 = fgraph.GetAirport("LAE");
    REQUIRE(airport4->destinations.size() == 2);
    REQUIRE(airport4->destinations.at(0).first == fgraph.GetAirport("GKA"));
    REQUIRE(airport4->destinations.at(0).second == 157);
}

TEST_CASE("right_arrivals", "[constructor]") {
    FlightGraph fgraph("data/test_airports.dat", "data/test_routes.dat");

    Airport* airport1 = fgraph.GetAirport("GKA");
    REQUIRE(airport1->arrivals.size() == 3);
    REQUIRE(airport1->arrivals.at(0)->iata == "MAG");
}

TEST_CASE("skip_duplicate_routes", "[constructor]") {
    FlightGraph fgraph("data/test_airports.dat", "data/test_routes.dat");

    Airport* airport8 = fgraph.GetAirport("GOH");
    REQUIRE(airport8->destinations.size() == 2);
}

TEST_CASE("copy_constructor", "[copy]"){
    FlightGraph fgraph("data/test_airports.dat", "data/test_routes.dat");
    FlightGraph fg1(fgraph);

    REQUIRE_FALSE(fgraph.GetAirport("GKA") == fg1.GetAirport("GKA"));
}

TEST_CASE("assignment", "[copy]"){
    FlightGraph fgraph("data/test_airports.dat", "data/test_routes.dat");
    FlightGraph fg2 = fgraph;

    REQUIRE_FALSE(fgraph.GetAirport("GKA") == fg2.GetAirport("GKA"));
}

TEST_CASE("assignment_2", "[copy]"){
    FlightGraph fgraph("data/test_airports.dat", "data/test_routes.dat");
    FlightGraph fg2("data/airports.dat", "data/routes.dat");

    REQUIRE_FALSE(fgraph.MapSize() == fg2.MapSize());

    fg2 = fgraph;

    REQUIRE_FALSE(fgraph.GetAirport("GKA") == fg2.GetAirport("GKA"));
    REQUIRE(fgraph.MapSize() == fg2.MapSize());
}

TEST_CASE("dfs_traversal", "[dfs]") {
    FlightGraph fgraph("data/test_airports.dat", "data/test_routes_dfs.dat");
    fgraph.DepthFirstTraverse("HGU");
    std::ifstream expected("tests/expected_dfs_output_1.txt");
    std::ifstream actual("bin/dfs_output.txt");
    std::string exp_line;
    std::string act_line;
    unsigned int count = 0;

    while (std::getline(actual, act_line)) {
        std::getline(expected, exp_line);
        count++;
        REQUIRE(exp_line == act_line);
    }
    REQUIRE(count == 7);

    expected.close();
    actual.close();

    fgraph.ClearCount();
    fgraph.DepthFirstTraverse("GOH");
    expected.open("tests/expected_dfs_output_2.txt");
    actual.open("bin/dfs_output.txt");
    count = 0;

    while (std::getline(actual, act_line)) {
        std::getline(expected, exp_line);
        count++;
        REQUIRE(exp_line == act_line);
    }
    REQUIRE(count == 2);
}

// Count connected components of JFK and ORD

TEST_CASE("heap_expected", "[heap]") {
    Airport air0;
    Airport air1;
    Airport air2;
    Airport air3;
    Airport air4;

    air0.dij_dist = 5;
    air1.dij_dist = 80;
    air2.dij_dist = 200;
    air3.dij_dist = 3;
    air4.dij_dist = 1;

    heap pri_queue;

    REQUIRE(pri_queue.empty());

    REQUIRE(pri_queue.root() == 1);

    pri_queue.push(&air0);
    REQUIRE(pri_queue.peek() == &air0);

    pri_queue.push(&air1);
    pri_queue.push(&air2);
    pri_queue.push(&air3);
    pri_queue.push(&air4);

    REQUIRE(pri_queue.peek() == &air4);

    pri_queue.pop();
    REQUIRE(pri_queue.peek() == &air3);

    pri_queue.pop();
    pri_queue.pop();
    pri_queue.pop();
    pri_queue.pop();

    REQUIRE(pri_queue.empty());
}

TEST_CASE("bfs_shortest_path", "[shortest_path]") {
    FlightGraph fg("data/test_airports.dat", "data/test_routes.dat");
    std::vector<Airport*> route = fg.ShortestPathAirports("THU", "UAK");
    REQUIRE(route.size() == 4);
    // Can't do multiple at a time? ClearCount() not working???
    // fg.ClearCount();
    // route = fg.ShortestPathAirports("GKA", "GOH");
    // REQUIRE(route.size() == 3);
}

TEST_CASE("bfs_shortest_path_not_found",  "[shortest_path]") {
    FlightGraph fg("data/test_airports.dat", "data/test_routes.dat");
    std::vector<Airport*> route = fg.ShortestPathAirports("UAK", "THU");
    REQUIRE(route.size() == 0);
}

TEST_CASE("dijkstra_shortest_path", "[shortest_path]") {
    /**
     * Unfortunately there are no ideal paths to test proper performance of Dijkstra's algorithm
     * in our small test dataset. However, we think this is a great workaround to showcase
     * correct behaviour.
     * 
     * CMI has two outgoing flights, one to ORD (O'Hare international), and one to DFW
     * (Dallas Fort-Worth international). Both airports have direct routes to JFK,
     * but going through ORD covers significantly less distance.
     * 
     * BFS has us going to DFW first, but Dijkstra's takes us to ORD first.
     * And you can use your intuition to verify the correctness as well. One cool rout I encourage
     * you to try is from WAW (Warsaw, Poland) to ANC (Anchorage, AL).
     */
    FlightGraph fg("data/airports.dat", "data/routes.dat");
    Airport* thu = fg.GetAirport("THU");
    std::vector<Airport*> route = fg.ShortestPathDistance("CMI", "JFK");
    REQUIRE(route.size() == 3);
    REQUIRE(route.at(1)->iata == "ORD");
}

// Use test routes to test pagerank. Make sure two lone airports have same value.
// Make sure THU < GKA