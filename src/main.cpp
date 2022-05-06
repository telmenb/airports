#include "flight_graph.hpp"

#include <iostream>

void break_line() {
    std::cout << "\n------------------------------------------------------------------------------\n\n";
}

void get_path(std::string& airports, std::string& routes) {
    std::cout << "Provide a custom dataset.\n"
        << "Please input airport data file path: ";
    std::cin >> airports;
    std::cout << "Please input routes data file path: ";
    std::cin >> routes;
    break_line();
}

void dfs(FlightGraph& fgraph) {
    std::cout << "Depth-first search traversal.\n"
        << "Please input the IATA code of the airport you'd like to start at: ";
    std::string iata;
    std::cin >> iata;
    break_line();

    std::string out_path;
    std::string choice;
    std::cout << "Where would you like to output?\n"
        << "1: \"bin/dfs_output.txt\"\n"
        << "2: Somewhere else...\n";
    std::cin >> choice;
    break_line();

    if (choice == "1") {
        out_path = "bin/dfs_output.txt";
    } else if (choice == "2") {
        std::cout << "Somewhere else...\n"
            << "Provide a custom output path: ";
        std::cin >> out_path;
        break_line();
    }

    if (fgraph.DepthFirstTraverse(iata, out_path)) {
        std::cout << "Your output has been printed to \"" << out_path << "\".\n\n";
    } else {
        std::cout << "Airport not found in our dataset. Please check your input and try again.\n\n";
    }
}

void bfs(FlightGraph& fgraph) {
    std::string departure;
    std::string arrival;
    std::cout << "Shortest path between two airports by least number of airports visited.\n"
        << "Please input departure IATA: ";
    std::cin >> departure;
    std::cout << "Please input arrival IATA: ";
    std::cin >> arrival;
    break_line();
    std::vector<Airport*> vec = fgraph.ShortestPathAirports(departure, arrival);
    if (vec.size() == 0) {
        std::cout << "No valid path found or invalid input, please try again.\n\n";
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
    std::cout << "Shortest path between two airports by least distance traveled.\n"
        << "Please input departure IATA: ";
    std::cin >> departure;
    std::cout << "Please input arrival IATA: ";
    std::cin >> arrival;
    break_line();
    std::vector<Airport*> vec = fgraph.ShortestPathDistance(departure, arrival);
    if (vec.size() == 0) {
        std::cout << "No valid path found or invalid input.\n\n";
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
        if (i == vec.size()) {
            break_line();
            std::cout << "Sorry, there are only " << i << " airports in the dataset\n";
            return;
        }
        std::cout << vec.at(i)->iata << " #" << i + 1 << " " << vec.at(i)->page_rank << std::endl;
    }
    std::cout << "\n";
}

int main() {
    std::cout << "\n-----------------------------Welcome to Airports!-----------------------------\n\n";

    std::cout << "Which dataset would you like to use?\n"
        << "1: Default dataset.\n"
        << "2: Test dataset.\n"
        << "3: Custom dataset.\n";
    std::string data_choice;
    std::cin >> data_choice;
    break_line();

    std::string airports_path;
    std::string routes_path;
    if (data_choice == "1") {
        airports_path = "data/airports.dat";
        routes_path = "data/routes.dat";
    } else if (data_choice == "2") {
        airports_path = "data/test_airports.dat";
        routes_path = "data/test_routes.dat";
    } else if (data_choice == "3") {
        get_path(airports_path, routes_path);
    } else {
        std::cout << "Invalid input, please try again.\n\n";
    }

    FlightGraph fgraph(airports_path, routes_path);

    if (fgraph.MapSize() == 0) {
        std::cout << "Bad file path. Exiting...\n";
        return 0;
    }

    std::cout << "Which of the following operations would you like to run?\n"
        << "1: Depth-first search traversal.\n"
        << "2: Shortest path between two airports.\n"
        << "3: Get a ranking of the most popular airports in the dataset.\n";

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