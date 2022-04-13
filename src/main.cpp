#include "flight_graph.hpp"

#include <iostream>

int main() {
    
    std::cout << "Hello world!\n";
    
    FlightGraph fg("data/test_airport.dat", "data/test_routes.dat");

    fg.DepthFirstTraverse("LAE");

    return 0;
}