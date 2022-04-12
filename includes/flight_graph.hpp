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
    FlightGraph(std::string airport_path, std::string route_path);

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

    Airport* GetAirport(std::string iata);
    size_t MapSize() { return map_.size(); }

private:
    // Hashmap to query airports
    std::map<std::string, std::pair<Airport*, int>> map_;
    
    // Helper functions
    void SetDestination(std::string dep_iata, std::string arr_iata);
    void ReadAirportData(std::string airport_path);
};