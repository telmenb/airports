#include "flight_graph.hpp"

FlightGraph::FlightGraph(std::string airport_path, std::string route_path) {
    ReadAirportData(airport_path);
    ReadRoutesData(route_path);
}

FlightGraph::FlightGraph(const FlightGraph& other){
    copy_graph(other);
}

FlightGraph::~FlightGraph() {
    delete_graph();
}

void FlightGraph::delete_graph(){
    for (auto it = map_.begin(); it != map_.end(); ++it) {
        delete it->second.first;
    }
    map_.clear();
}

void FlightGraph::copy_graph(const FlightGraph& other){
    for (auto it = other.map_.begin(); it != other.map_.end(); ++it){
        Airport* otr_airport = it->second.first;
        Airport *airport_ = new Airport(otr_airport->iata, otr_airport->name, otr_airport->country,
                                        otr_airport->latitude, otr_airport->longitude);
        map_[it->first] = std::make_pair(airport_, it->second.second);
    }
}

const FlightGraph& FlightGraph::operator=(const FlightGraph& other){
    delete_graph();
    copy_graph(other);
    return *this;
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

bool FlightGraph::HasVisited(std::string iata) {
    auto query = map_.find(iata);
    if (query == map_.end())
        return true;
    return query->second.second != 0;
}

void FlightGraph::SetVisited(std::string iata) {
    auto query = map_.find(iata);
    if (query == map_.end())
        return;
    query->second.second = 1;
}

int CalculateDistance(double lat1, double lon1, double lat2, double lon2) {
    double d_lat = (lat2 - lat1) * M_PI / 180.0;
    double d_lon = (lon2 - lon1) * M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formula
    double angle = pow(sin(d_lat / 2), 2) + pow(sin(d_lon / 2), 2) * cos(lat1) * cos(lat2);
    double computation = 2 * asin(sqrt(angle));
    double radius = 6371;
    return (int) (radius * computation);
}

void FlightGraph::DepthFirstTraverse(std::string start){
    std::ofstream ostr;
    ostr.open ("bin/dfs_output.txt");
    Airport *start_ = GetAirport(start);
    std::stack<Airport*> dfs_stack;

    dfs_stack.push(start_);
    while(!dfs_stack.empty()){
        Airport* cur = dfs_stack.top();
        if (HasVisited(cur->iata)) {
            dfs_stack.pop();
            continue;
        }
        for(size_t i = 0; i < cur->destinations.size(); i++) {
            Airport* destination = cur->destinations.at(i).first;
            if (!HasVisited(destination->iata)) {
                dfs_stack.push(destination);
            }
        }
        ostr << cur->iata << "\n";
        SetVisited(cur->iata);
    }

    ostr.close();
}

std::vector<Airport*> FlightGraph::ShortestPathAirports(std::string start, std::string end) {
    Airport* origin = GetAirport(start);
    if (!origin) return std::vector<Airport*> {NULL};               // Airport not found
    
    std::queue<Airport*> bfs_queue;                                 // Queue used for BFS
    std::map<Airport*, Airport*> track;                             // Map to keep track of previous airport in path
    bfs_queue.push(origin);
    track[origin] = NULL;
    while (!bfs_queue.empty()) {
        Airport* cur = bfs_queue.front();
        if (cur->iata == end) break;

        for (size_t i = 0; i < cur->destinations.size(); i++) {
            Airport* dest = cur->destinations.at(i).first;
            if (!HasVisited(dest->iata)) {
                if (track.find(dest) == track.end()) {
                    track[dest] = cur;
                }
                bfs_queue.push(dest);
            }
        }

        SetVisited(cur->iata);
        bfs_queue.pop();
    }

    if (bfs_queue.empty()) {                                        // No valid path found
        return std::vector<Airport*>();
    }

    std::vector<Airport*> to_return;                                // Backtracking path
    auto iter = track.find(bfs_queue.front());
    while (iter->second != NULL) {
        to_return.push_back(iter->first);
        iter = track.find(iter->second);
    }
    to_return.push_back(iter->first);

    std::reverse(to_return.begin(), to_return.end());
    return to_return;
}

std::vector<Airport*> FlightGraph::ShortestPathDistance(std::string start, std::string end) {
    Airport* origin = GetAirport(start);
    Airport* dest = GetAirport(end);
    if (!origin || !dest) return std::vector<Airport*> {NULL};      // Airport not found
    
    heap priority_queue;                                            // Priority queue querying smallest distance route
    std::map<Airport*, Airport*> track;                             // Map to keep track of previous airport in path
    track[origin] = NULL;
    origin->dij_dist = 0;
    priority_queue.push(origin);
    while (!priority_queue.empty() && priority_queue.peek() != dest) {
        Airport* cur = priority_queue.peek();

        for (size_t i = 0; i < cur->destinations.size(); i++) {
            std::pair<Airport*, int> neighbor = cur->destinations.at(i);
            if (cur->dij_dist + neighbor.second < neighbor.first->dij_dist
                                     && !HasVisited(neighbor.first->iata)) {
                neighbor.first->dij_dist = cur->dij_dist + neighbor.second;
                track[neighbor.first] = cur;
                priority_queue.push(neighbor.first);
            }
        }

        SetVisited(cur->iata);
        priority_queue.pop();
    }
    
    if (priority_queue.empty()) {                                   // No valid path found
        return std::vector<Airport*>();
    }

    std::vector<Airport*> to_return;                                // Backtracking path
    auto iter = track.find(dest);
    while (iter->second != NULL) {
        to_return.push_back(iter->first);
        iter = track.find(iter->second);
    }
    to_return.push_back(iter->first);

    std::reverse(to_return.begin(), to_return.end());
    return to_return;
}

bool sort_by_desc_sec(const std::pair<Airport*, int>& a,
                      const std::pair<Airport*, int>& b) {
    return a.second > b.second;
}

int FlightGraph::rand_num_map(){
    int rand = std::rand() % map_.size();
    return rand;
}

std::vector<std::pair<Airport*, int>> FlightGraph::GetRanking(size_t iterations){
    //start at a random node
    std::srand(time(0));
    auto iter = std::next(map_.begin(), rand_num_map()); //select random airport to start
    iter->second.second += 1; //increment count of the airport;
    Airport* surfer = iter->second.first;

    //go to any of the neighbors 85% of the time;
    //go to a completely random guy 15% of the time;
    for (size_t i = 0; i < iterations; i++){ //idk how many times to do it i just picked 10,000 randomly
        int damp = std::rand() % 100;
        if (damp < 86 && surfer->destinations.size() != 0){
            surfer = (surfer->destinations[std::rand() % surfer->destinations.size()]).first; //get a random neighbor
            (map_[surfer->iata]).second += 1; //increment count of the airport
        }
        else{
            iter = std::next(map_.begin(), rand_num_map());
            (map_[surfer->iata]).second += 1; //increment count of the airport;
        }
    }


    std::vector<std::pair<Airport*, int>> to_return;
    for (auto it = map_.begin(); it != map_.end(); it++){
        to_return.push_back((*it).second);
    }

    std::sort(to_return.begin(), to_return.end(), sort_by_desc_sec);
    return to_return;
}