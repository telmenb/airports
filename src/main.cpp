#include "flight_graph.hpp"

#include <iostream>

int main() {
    
    std::cout << "Hello world!\n";
    
    FlightGraph fg("data/test_airports.dat", "data/test_routes.dat");
    // Airport* thu = fg.GetAirport("THU");
    // for (size_t i = 0; i < thu->destinations.size(); i++) {
    //     std::pair<Airport*, int> dest_pair = thu->destinations.at(i);
    //     if (dest_pair.first->iata == "POM") {
    //         dest_pair.second = 20000;
    //         break;
    //     }
    // }

    std::vector<Airport*> vec = fg.ShortestPathDistance("LAE", "GKA");

    std::cout << "vec size: " << vec.size() << std::endl;

    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec.at(i)->iata << std::endl;
        if (i < vec.size() - 1) {
            std::cout << CalculateDistance(std::stod(vec.at(i)->latitude), std::stod(vec.at(i)->longitude),
            std::stod(vec.at(i + 1)->latitude), std::stod(vec.at(i + 1)->longitude)) << std::endl;
        }
    }

    // std::vector<std::pair<Airport*, int>> ranking = fg.GetRanking(1000);

    // for (size_t i = 0; i < 10; i++) {
    //     std:: cout << ranking.at(i).first->iata << ": " << ranking.at(i).second << std::endl;
    // }

    return 0;
}