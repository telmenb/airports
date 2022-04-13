#include "flight_graph.hpp"

FlightGraph::FlightGraph(std::string airport_path, std::string route_path) {
    ReadAirportData(airport_path);
    ReadRoutesData(route_path);
}

FlightGraph::~FlightGraph() {
    for (auto it = map_.begin(); it != map_.end(); ++it) {
        delete it->second.first;
    }
}

void FlightGraph::ReadAirportData(std::string airport_path) {
    std::vector<std::string> line_vec;
    std::string line;
    std::ifstream ifs(airport_path);
    while (std::getline(ifs, line)) {
        line_vec.clear();
        
        std::string cell;
        std::stringstream sstr(line);
        while (std::getline(sstr, cell, ',')) {
            if (cell.at(0) == '"')
                cell = cell.substr(1, cell.length() - 2);
            
            line_vec.push_back(cell);
        }

        if (line_vec.size() != 14 || line_vec.at(4).length() != 3) continue;

        std::string iata = line_vec.at(4);
        std::string name = line_vec.at(1);
        std::string country = line_vec.at(3);
        std::string latitude = line_vec.at(6);
        std::string longitude = line_vec.at(7);
        Airport* airport = new Airport(iata, name, country, latitude, longitude);
        map_[iata] = std::make_pair(airport, 0);
    }
}

void FlightGraph::ReadRoutesData(std::string routes_path) {
    std::vector<std::string> line_vec;
    std::string line;
    std::ifstream ifs(routes_path);
    while (std::getline(ifs, line)) {
        line_vec.clear();

        std::string cell;
        std::stringstream sstr(line);
        while (std::getline(sstr, cell, ',')) {
            line_vec.push_back(cell);
        }

        if (line_vec.size() != 9 || line_vec.at(7) != "0") continue;

        Airport* src = GetAirport(line_vec.at(2));
        Airport* dest = GetAirport(line_vec.at(4));

        if (!src || !dest) continue;

        SetDestination(src, dest);
    }
}

void FlightGraph::SetDestination(Airport* src, Airport* dest) {
    for (size_t i = 0; i < src->destinations.size(); i++) {
        if (src->destinations.at(i).first == dest) return;
    }
    int distance = CalculateDistance(std::stod(src->latitude),
                                     std::stod(src->longitude),
                                     std::stod(dest->latitude),
                                     std::stod(dest->longitude));

    src->destinations.push_back(std::make_pair(dest, distance));
}

Airport* FlightGraph::GetAirport(std::string iata) {
    auto query = map_.find(iata);
    if (query == map_.end())
        return NULL;
    return query->second.first;
}

const std::vector<std::pair<Airport*, int>>& FlightGraph::GetDestinations(Airport* src) const {
    if (src) {
        return src->destinations;
    }
    throw std::runtime_error("No airport");
}

 int CalculateDistance(double lat1, double lon1, double lat2, double lon2) {
    double d_lat = (lat2 - lat1) * M_PI / 180.0;
    double d_lon = (lon2 - lon1) * M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double angle = pow(sin(d_lat / 2), 2) + pow(sin(d_lon / 2), 2) * cos(lat1) * cos(lat2);
    double computation = 2 * asin(sqrt(angle));
    double radius = 6371;
    return (int) (radius * computation);
}