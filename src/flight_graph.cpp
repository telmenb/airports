#include "../includes/flight_graph.hpp"

FlightGraph::FlightGraph() {
    std::vector<std::string> line_vec;
    std::string line;
    std::ifstream ifs("data/test_data.dat");
    while (std::getline(ifs, line)) {
        line_vec.clear();
        
        std::string cell;
        std::stringstream sstr(line);

        while (std::getline(sstr, cell, ',')) {
            if (cell.at(0) == '"') {
                cell = cell.substr(1, cell.length() - 2);
            }
            std::cout << cell << std::endl;
            line_vec.push_back(cell);
        }
        Airport* airport = new Airport(line_vec.at(4), line_vec.at(7), line_vec.at(6), line_vec.at(1), line_vec.at(3));
        map_[line_vec.at(4)] = std::make_pair(airport, 0);
    }
}

FlightGraph::~FlightGraph() {
    for (auto it = map_.begin(); it != map_.end(); ++it) {
        delete it->second.first;
    }
}