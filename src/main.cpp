#include "flight_graph.hpp"

#include <iostream>

int main() {
    
    std::cout << "Hello world!\n";
    
    FlightGraph fg("data/airports.dat", "data/routes.dat");

    std::vector<Airport*> vec = fg.ShortestPathDistance("CMI", "JFK");

    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec.at(i)->iata << std::endl;
        if (i < vec.size() - 1) {
            std::cout << CalculateDistance(std::stod(vec.at(i)->latitude), std::stod(vec.at(i)->longitude),
            std::stod(vec.at(i + 1)->latitude), std::stod(vec.at(i + 1)->longitude)) << std::endl;
        }
    }

    return 0;
}