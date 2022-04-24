#pragma once

#include "airport.hpp"

#include <map>
#include <vector>
#include <string>
#include <utility>
#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>

class FlightGraph {
public:
    // Default constructor
    FlightGraph(std::string airport_path, std::string route_path);

    // Rule of three --------------------------------------
    FlightGraph(const FlightGraph& other);
    const FlightGraph& operator=(const FlightGraph& other);
    ~FlightGraph();
    //-----------------------------------------------------

    //DFS traversal
    void DepthFirstTraverse(std::string start);

    // BFS shortest path
    std::vector<Airport*> ShortestPathAirports(std::string start, std::string end);

    // Dijkstra's shortest path
    // std::vector<Airport*> ShortestPathDistance(std::string start, std::string end);

    // PageRank
    // std::vector<Airport*> GetRanking(int num);

    Airport* GetAirport(std::string iata);
    bool HasVisited(std::string iata);
    void SetVisited(std::string iata);
    size_t MapSize() const { return map_.size(); }
    const std::vector<std::pair<Airport*, int>>& GetDestinations(Airport* src) const;

private:
    // Hashmap to query airports
    std::map<std::string, std::pair<Airport*, int>> map_;
    
    // Helper functions
    void ReadAirportData(std::string airport_path);
    void ReadRoutesData(std::string routes_path);
    void SetDestination(Airport* src, Airport* dest);
    void delete_graph();
    void copy_graph(const FlightGraph& other);
};

int CalculateDistance(double lat1, double lon1, double lat2, double lon2);