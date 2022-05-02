#pragma once

#include <string>
#include <vector>
#include <utility>

// Constant for more than maximum possible distance between two points on earth
const int MAX_DIST = 50000;

/**
 * Airport: a struct used as a node in the graph representing an Airport
 * 
 * @author Telmen Bayarsaikhan, Anish Sabnis
 */
struct Airport {
    /**
     * Construct a new default Airport object.
     * For testing purposes only.
     */
    Airport() {}

    /**
     * Construct a new Airport object.
     * 
     * @param code The IATA code of the airport
     * @param name The name of the airport
     * @param country The country the airport belongs to
     * @param lat The real world latitude of the airport
     * @param lng The real world longitude of the airport
     */
    Airport(std::string code, std::string name, std::string country, std::string lat, std::string lng)
                             : iata(code), longitude(lng), latitude(lat), name(name), country(country) {}

    // Member variables
    std::string iata;
    std::string longitude;
    std::string latitude;
    std::string name;
    std::string country;
    int dij_dist = MAX_DIST;        // dij_dist initialized to MAX_DIST for Dijkstra's Algorithm
    double page_rank = 1;           // page_rank initialized to 1 for all airports

    /**
     * Adjacency list vector of destination Airport*, int pairs.
     * Contains pointers to destination airports with
     * their respective edge weights, measured in kilometers.
     */
    std::vector<std::pair<Airport*, int>> destinations;

    /**
     * Adjacency list to keep track of incoming edges
     * Used in GetRanking method to recalculate pagerank value 
     */
    std::vector<Airport*> arrivals;

    /**
     * Comparison operator for Airport objects based on their dij_dist.
     * Used in implementing a min-priority queue of Airport objects (see heap.hpp).
     * 
     * @param other The airport to compare with
     * @return true other has less dij_dist
     * @return false other has more dij_dist
     */
    bool operator>(const Airport*& other) { return dij_dist > other->dij_dist; }
};