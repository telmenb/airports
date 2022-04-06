#pragma once

#include "airport.hpp"

#include <map>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>

class FlightGraph {
public:
    // Default constructor
    FlightGraph();

    // Rule of three --------------------------------------
    // FlightGraph(const FlightGraph& other);
    // const FlightGraph& operator=(const FlightGraph& other);
    ~FlightGraph();
    //-----------------------------------------------------

    // DFS traversal
    // void DepthFirstTraverse(std::string start);

    // BFS shortest path
    // std::vector<Airport*> ShortestPathAirports(std::string start, std::string end);

    // Dijkstra's shortest path
    // std::vector<Airport*> ShortestPathDistance(std::string start, std::string end);

    // PageRank
    // std::vector<Airport*> GetRanking(int num);

private:
    // Hashmap to query airports
    std::map<std::string, std::pair<Airport*, int>> map_;
    
    // Helper functions
    void SetDestination(std::string dep_iata, std::string arr_iata);
};