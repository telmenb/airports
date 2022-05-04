#pragma once

#include "airport.hpp"
#include "heap.hpp"

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

/**
 * FlightGraph: Main wrapper object for graph operations.
 * 
 * @authors Anish Sabnis, Telmen Bayarsaikhan
 */
class FlightGraph {
public:
    /**
     * Construct a new FlightGraph object with the given file paths.
     * 
     * @param airport_path The file path to the airport dataset
     * @param route_path  The file path to the routes dataset
     */
    FlightGraph(std::string airport_path, std::string route_path);

    /**
     * Construct a new FlightGraph object from a passed in FlightGraph.
     * 
     * @param other The FlightGraph object to copy
     */
    FlightGraph(const FlightGraph& other);

    /**
     * Construct or otherwise rewrite a FlightGraph object from a passed in FlightGraph.
     * 
     * @param other The FlightGraph object to copy
     * @return Reference to newly written FlightGraph
     */
    const FlightGraph& operator=(const FlightGraph& other);

    /* Free all memory associated with the FlightGraph object. */
    ~FlightGraph();

    /**
     * Perform a simple Depth-First Traversal starting at a specified airport
     * and output the results to "bin/dfs_output.txt".
     * 
     * Output should include all members of startpoint's connected component.
     * 
     * @param start The IATA code of the airport you'd like to start the DFS traversal
     * @return Whether the operation was successful or not
     */
    bool DepthFirstTraverse(std::string start);

    /**
     * Get the shortest path between two airports using a Breadth-First Search.
     * 
     * This should return the path with least number of airports visited.
     * 
     * @param start Start airport IATA
     * @param end Destination airport IATA
     * @return Vector of Airport* representing the path, including start and end-points
     */
    std::vector<Airport*> ShortestPathAirports(std::string start, std::string end);

    /**
     * Get the shortest path between two airports using Dijkstra's Algorithm.
     * 
     * This should return the path with least distance traveled.
     * 
     * @param start Start airport IATA
     * @param end Destination airport IATA
     * @return Vector of Airport* representing the path, including start and end-points
     */
    std::vector<Airport*> ShortestPathDistance(std::string start, std::string end);

    /**
     * Rank all airports by popularity using Google's PageRank algorithm.
     * 
     * Convergence is achieved after an undetermined number of iterations. Set to
     * to 100 by default. Damping factor is 0.15 by default.
     * 
     * @param iterations Number of times to calculate page_rank value for each airport
     * @return Vector of all airports in the dataset, ranked by their page_rank value
     */
    std::vector<Airport*> GetRanking(size_t iterations);

    /**
     * Get a pointer to an airport object in the graph.
     * 
     * Returns NULL if not found in map_.
     * 
     * @param iata IATA code of queried airport 
     * @return Pointer to desired airport
     */
    Airport* GetAirport(std::string iata);

    /* Resets the int of pair value stored in map_. Used in testing. */
    void ClearCount();

    /* Returns the size of map_. */
    size_t MapSize() const { return map_.size(); }

private:
    /**
     * The primary map used to keep track of airports stored on heap memory.
     * 
     * Maps a string IATA code to a pair of airport and int. The integer
     * primarily serves as an indicator to whether or not the airport has
     * already been visited or not in a search or traversal.
     * 
     * Also used in freeing associated airports' memory at the end of
     * FlightGraph's lifecycle.
     */
    std::map<std::string, std::pair<Airport*, int>> map_;
    
    /**
     * Helper used in FlightGraph constructor to read airports dataset
     * and create Airport objects.
     * 
     * @param airport_path File path to airport data
     */
    void ReadAirportData(std::string airport_path);

    /**
     * Helper used in FlightGraph constructor to read routes dataset and associate Airport objects
     * to each other.
     * 
     * @param routes_path File path to routes data
     */
    void ReadRoutesData(std::string routes_path);

    /**
     * Helper method used by ReadRoutesData to add dest to src's destination adjacency list
     * with proper distance as weight.
     * 
     * Makes sure no duplicates are added when pushing to adjacency vector.
     * 
     * @param src Airport whose destination vector is being added to
     * @param dest Airport being added
     */
    void SetDestination(Airport* src, Airport* dest);

    /**
     * Helper method used to determine whether an airport has already been visited
     * in a search or traversal.
     * 
     * @param iata IATA code of airport to check
     * @return Whether airport has been visited
     */
    bool HasVisited(std::string iata);

    /**
     * Helper method used to set an airport as visited in a search or traversal.
     * 
     * @param iata IATA code of airport to mark visited
     */
    void SetVisited(std::string iata);

    /* Helper method used to free associated airport objects from heap memory. */
    void delete_graph();

    /**
     * Helper method used to copy over another FlightGraph's components.
     * 
     * @param other The FlightGraph to copy
     */
    void copy_graph(const FlightGraph& other);
};

/**
 * Function used to find the distance, in kilometers, between two points on earth.
 * 
 * @param lat1 Latitude of first point
 * @param lon1 Longitude of first point
 * @param lat2 Latitude of second point
 * @param lon2 Longitude of second point
 * @return The distance between the two points in km
 */
int CalculateDistance(double lat1, double lon1, double lat2, double lon2);