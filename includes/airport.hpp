#pragma once

#include <string>
#include <vector>
#include <utility>

const int MAX_DIST = 30000;

struct Airport {
    Airport() {}
    Airport(std::string code, std::string name, std::string country, std::string lat, std::string lng)
        : iata(code), longitude(lng), latitude(lat), name(name), country(country) {}

    std::string iata;
    std::string longitude;
    std::string latitude;
    std::string name;
    std::string country;
    int dij_dist = MAX_DIST;

    // Adjacency list of destinations
    std::vector<std::pair<Airport*, int>> destinations;
    bool operator>(const Airport*& other) { return dij_dist > other->dij_dist; }
};