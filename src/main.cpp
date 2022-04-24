#include "flight_graph.hpp"

#include <iostream>

int main() {
    
    std::cout << "Hello world!\n";
    
    FlightGraph fg("data/airports.dat", "data/routes.dat");

    std::vector<Airport*> vec = fg.ShortestPathAirports("CMI", "POM");

    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec.at(i)->iata << std::endl;
    }

    return 0;
}