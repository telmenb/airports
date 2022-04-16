#include "flight_graph.hpp"

#include <iostream>

int main() {
    
    std::cout << "Hello world!\n";
    
    FlightGraph fg("data/test_airports.dat", "data/test_routes.dat");

    fg.DepthFirstTraverse("HGU");

    return 0;
}