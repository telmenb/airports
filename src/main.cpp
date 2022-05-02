#include "flight_graph.hpp"

#include <iostream>

int main() {
    FlightGraph fgraph("data/airports.dat", "data/routes.dat");

    std::cout << "Which of the following operations would you like to run?\n"
        << "1: Depth-first search traversal.\n"
        << "2: Shortest path between two airports.\n"
        << "3: Get a ranking of the most popular airports in the world.\n";

    std::string choice;
    std::cin >> choice;

    if (choice == "1") {
        std::cout << "Please input the IATA code of the airport you'd like to start at: ";
        std::string iata;
        std::cin >> iata;
        if (fgraph.DepthFirstTraverse(iata)) {
            std::cout << "Your output has been printed to \"bin/dfs_output.txt\".\n";
        } else {
            std::cout << "Airport not found in our dataset. Please check your input and try again.\n";
        }

    } else if (choice == "2") {
        std::cout << "1: By least number of airports visited.\n"
            << "2: By least of distance traveled.\n";
        std::cin >> choice;

        std::string departure;
        std::string arrival;
        if (choice == "1") {
            std::cout << "Please input departure IATA: ";
            std::cin >> departure;
            std::cout << "\nPlease input arrival IATA: ";
            std::cin >> arrival;
            std::vector<Airport*> vec = fgraph.ShortestPathAirports(departure, arrival);
            if (vec.size() == 0) {
                std::cout << "\nNo valid path found\n";
                return 0;
            }
            for (size_t i = 0; i < vec.size(); i++) {
                if (i == 0) std::cout << vec.at(i)->iata;
                else std::cout << " -> " << vec.at(i)->iata;
            }
            std::cout << std::endl;

        } else if (choice == "2") {
            std::cout << "Please input departure IATA: ";
            std::cin >> departure;
            std::cout << "\nPlease input arrival IATA: ";
            std::cin >> arrival;
            std::vector<Airport*> vec = fgraph.ShortestPathDistance(departure, arrival);
            if (vec.size() == 0) {
                std::cout << "\nNo valid path found\n";
                return 0;
            }
            for (size_t i = 0; i < vec.size(); i++) {
                if (i == 0) std::cout << vec.at(i)->iata;
                else std::cout << " -> " << vec.at(i)->iata;
            }
            std::cout << std::endl;
            
        } else {
            std::cout << "Invalid input, please try again.\n";
        }

    } else if (choice == "3") {
        std::cout << "How many top airport rankings would you like?\n";
        std::string str;
        std::cin >> str;
        size_t num;
        try {
            int input = std::stoi(str);
            num = (size_t) input;
        } catch (std::invalid_argument e) {
            std::cout << "Invalid input, please try again.\n";
            return 0;
        }
        std::vector<Airport*> vec = fgraph.GetRanking(100);
        for (size_t i = 0; i < num; i++) {
            std::cout << i+1 << ": " << vec.at(i)->iata << std::endl;
        }

    } else {
        std::cout << "Invalid input, please try again.\n";
    }

    return 0;
}