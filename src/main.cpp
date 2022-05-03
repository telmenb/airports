#include "flight_graph.hpp"

#include <iostream>

void break_line() {
    std::cout << "\n------------------------------------------------------------------------------\n\n";
}

void dfs(FlightGraph& fgraph) {
    std::cout << "Depth-first search traversal\n"
        << "Please input the IATA code of the airport you'd like to start at: ";
    std::string iata;
    std::cin >> iata;
    break_line();
    if (fgraph.DepthFirstTraverse(iata)) {
        std::cout << "Your output has been printed to \"bin/dfs_output.txt\".\n\n";
    } else {
        std::cout << "Airport not found in our dataset. Please check your input and try again.\n\n";
    }
}

void bfs(FlightGraph& fgraph) {
    std::string departure;
    std::string arrival;
    std::cout << "Shortest path between two airports by least number of airports visited\n"
        << "Please input departure IATA: ";
    std::cin >> departure;
    std::cout << "Please input arrival IATA: ";
    std::cin >> arrival;
    break_line();
    std::vector<Airport*> vec = fgraph.ShortestPathAirports(departure, arrival);
    if (vec.size() == 0) {
        std::cout << "No valid path found or invalid input, please try again\n\n";
        return;
    }
    for (size_t i = 0; i < vec.size(); i++) {
        if (i == 0) std::cout << vec.at(i)->iata;
        else std::cout << " -> " << vec.at(i)->iata;
    }
    std::cout << "\n\n";
}

void dijkstra(FlightGraph& fgraph) {
    std::string departure;
    std::string arrival;
    std::cout << "Shortest path between two airports by least distance traveled\n"
        << "Please input departure IATA: ";
    std::cin >> departure;
    std::cout << "Please input arrival IATA: ";
    std::cin >> arrival;
    break_line();
    std::vector<Airport*> vec = fgraph.ShortestPathDistance(departure, arrival);
    if (vec.size() == 0) {
        std::cout << "No valid path found\n\n";
        return;
    }
    for (size_t i = 0; i < vec.size(); i++) {
        if (i == 0) std::cout << vec.at(i)->iata;
        else std::cout << " -> " << vec.at(i)->iata;
    }
    std::cout << "\n\n";
}

void page_rank(FlightGraph& fgraph) {
    std::cout << "How many top airport rankings would you like?\n";
    std::string str;
    std::cin >> str;
    break_line();
    size_t num;
    try {
        int input = std::stoi(str);
        if (input < 0) throw std::invalid_argument("no negative ranking");
        num = (size_t) input;
    } catch (std::invalid_argument e) {
        std::cout << "Invalid input, please try again.\n\n";
        return;
    }
    std::vector<Airport*> vec = fgraph.GetRanking(100);
    for (size_t i = 0; i < num; i++) {
        std::cout << vec.at(i)->iata << " #" << i + 1 << " " << vec.at(i)->page_rank << std::endl;
    }
    std::cout << "\n";
}

int main() {
    FlightGraph fgraph("data/airports.dat", "data/routes.dat");
    std::cout << "\n-----------------------------Welcome to Airports!-----------------------------\n\n";

    std::cout << "Which of the following operations would you like to run?\n"
        << "1: Depth-first search traversal.\n"
        << "2: Shortest path between two airports.\n"
        << "3: Get a ranking of the most popular airports in the world.\n";

    std::string choice;
    std::cin >> choice;
    break_line();

    if (choice == "1") {
        dfs(fgraph);

    } else if (choice == "2") {
        std::cout << "Shortest path between two airports\n"
            << "1: By least number of airports visited.\n"
            << "2: By least distance traveled.\n";
        std::cin >> choice;
        break_line();

        if (choice == "1") {
            bfs(fgraph);
        } else if (choice == "2") {
            dijkstra(fgraph);
        } else {
            std::cout << "Invalid input, please try again.\n\n";
        }

    } else if (choice == "3") {
        page_rank(fgraph);

    } else {
        std::cout << "Invalid input, please try again.\n\n";
    }

    return 0;
}