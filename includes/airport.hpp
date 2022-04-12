#pragma once

#include <string>
#include <vector>
#include <utility>

struct Airport {
    Airport(std::string code, std::string name, std::string country, std::string lat, std::string lng)
        : iata(code), longitude(lng), latitude(lat), name(name), country(country) {}

    std::string iata;
    std::string longitude;
    std::string latitude;
    std::string name;
    std::string country;

    // Adjacency list of destinations
    std::vector<std::pair<Airport*, int>> destinations;
};