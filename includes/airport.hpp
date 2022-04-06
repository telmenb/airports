#pragma once

struct Airport {
    std::string iata;
    std::string longitude;
    std::string latitude;
    std::string name;
    std::string country;
    std::vector<Airport*, int> destinations;
};