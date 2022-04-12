#include "flight_graph.hpp"

#include <iostream>

int main() {
    
    std::cout << "Hello world!\n";
    
    FlightGraph fg("data/airports.dat", "data/routes.dat");

    return 0;
}