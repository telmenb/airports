#include "flight_graph.hpp"

#include <iostream>

int main() {
    
    std::cout << "Hello world!\n";
    
    FlightGraph fg("data/test_airport.dat", "data/test_routes.dat");

    FlightGraph fg1(fg);

    FlightGraph fg2 = fg;

    return 0;
}