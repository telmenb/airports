# Project Proposal

## Leading Question

Using a set of route and airport data, the leading questions we hope to answer with our project are: “What is the shortest flight path between two airports?” and “What are the most popular airports in the world?”. We wish to develop a general search tool where users can input the IATA codes of two airports accompanied by a flag command, and depending on which flag was input, the output will display the shortest path between the two airports either in terms of least number of airports visited or least amount of real-world distance traveled. We also hope to allow users to input a number n and receive a list of the n most popular airports within the dataset. Our general data structure will be a weighted, directed graph where the nodes represent airports and edges represent flights between airports. The weights of the edges will be determined by using the real-world distance between two airports - calculated by using the Haversine formula on their respective latitude and longitudinal data. We will use a simple Breadth-First Search approach to find the path with the least number of nodes visited and use Dijkstra’s algorithm to find the shortest real-world path from our weighted graph. We will also utilize Google’s famous PageRank algorithm to rank our airports in terms of popularity. On top of the aforementioned use cases, we plan to offer users the option to input only one airport IATA code and receive an itinerary of all airports in the dataset using a Depth-First Traversal starting at the user-entered airport.

## Data Acquisition and Processing

### Data Format:

We have two separate datasets of airport and route information from [OpenFlights](https://openflights.org/data.html), a publicly accessible provider. Both datasets are formatted as comma-separated values (CSV) lists with over 7600 and 67000 entries for airports and routes respectively. The airport data is entered as: *[Airport ID,Name,City,Country,IATA,ICAO,Latitude,Longitude,Altitude,Timezone,DST,Tz database time zone,Type,Source]*, and the routes data is entered as: *[Airline,Airline ID,Source airport,Source airport ID,Destination airport,Destination airport ID,Codeshare,Stops,Equipment]*.

### Data Correction:

We will not be using the entirety of both datasets in our project, thus much will be required to sanitize and process the data. From the airport dataset, we will ignore entries that do not have a 3-letter IATA code since that is our primary method to represent and hash our airports. In the routes dataset there is a bigger need for careful correction. In the event either the Source airport or Destination airport parameters for the entry are using ICAO 4-letter codes instead of our chosen convention of IATA 3-letter codes, we will disregard the entry. Additionally, if the Stops parameter is filled with anything other than 0, we will disregard as we are only interested in direct routes between two airports. With that, we are confident that our data will be ready for use. If the situation presents itself where we need to add more safeguards to other parameters in our data, regular expressions can be utilized to assert expected behavior in the fields.

### Data Storage:

For data storage, our two .dat files will be stored in the “data” directory within our project. We will be storing our Nodes in heap memory as it is larger and less restrictive. A single, general-purpose object will be used to store Node pointers through hashing IATA codes, and for methods to complete graph operations. The local object of our graph will contain a map that hashes IATA to <Node*, int> pairs. The integer will be used in the DFS traversal to mark our nodes as visited, as well as count the number of visits for PageRank. Our node, representing an airport, will have its appropriate member variables i.e IATA code, latitude, longitude, etc. Among these data members will be an adjacency list vector representing that node’s destinations. The vector will be of type <Node*, int> pairs where the first value is a pointer to the destination, while the second value is the weight of that edge found through the Haversine formula. For the sake of simplicity, and because we view it as appropriate for the scope of this project, we will be using the C++ standard library’s implementations of vector, map, and pair data structures.

## Graph Algorithms

### Depth-First Traversal

A simple traversal to visit every node in the graph once. It will receive an IATA code as a string from user input and use our internal hashmap to find and use the node as the starting point of the traversal. When marking nodes as visited, it will also be printing the IATA codes of the respective airports to standard output - thus by the end, we will have an exhaustive list of all the airports in the graph. In the event a user submits invalid input, either non-IATA or IATA codes which we do not handle, there will be an error message output. Runtime is O(n), where n is the number of nodes in the graph, as we will be visiting every single node in the graph. The space complexity is anticipated to be at most O(b*m) where b is the maximum branching factor of the graph and m is the length of the longest path.

### Dijkstra's Algorithm:

We will use Dijkstra’s algorithm to find the shortest path between two airports with respect to real-world distance. It will receive two IATA codes as strings from user input and consider them departure and arrival points respectively. We will have to use our internal hashmap to retrieve node addresses similar to our traversal. Because Dijkstra’s algorithm requires edges to be weighted, we’ve designed our adjacency lists to store <Node*, int> pairs where accessing destination and weight of edges are greatly simplified. After the shortest path is determined, a vector of Node* sequenced from departure to arrival will be returned.  Invalid inputs will be handled similarly to the traversal mentioned above. Using a min-heap, Dijkstra’s algorithm runs in O((n+m)log(n)) where n is the number of nodes in the graph and m is the number of edges in the graph. Space complexity is O(n + m).

### PageRank:

PageRank will be used primarily for the task of ranking airports within the dataset. It will receive the starting node in the graph, number of random surfs to complete, and the damping factor as input. Our function will randomly surf through the graph and count how many times individual nodes are being visited. To cover the possibility of unconnected components, (1 - damping factor)\*100% of the time, our surfer will shift to a random node on the graph and continue its surf from there. After the surfer has completed its run, the function returns a vector of Node*, sorted from most to least visited. The algorithm is expected to run in O(n*s + nlog(n)) time - since we need to sort the vector afterwards - where n is the number of nodes in the graph and s is the number of random surfs to complete. Space complexity is expected to be O(n).

## Timeline

Data acquisition has already been achieved at the time of writing. Data processing is anticipated to take one week; this should include parsing input to sanitize data and remove unnecessary parameters. We already have a rough outline of the design structure, so we are not anticipating it would take more than a week to finalize. The above-mentioned two can be developed simultaneously. The graph structure constructor is expected to be completed by week 3, and the rest of the development time is allocated for the graphing algorithms as well as traversal. Ideally, we would like to have the Depth-First Traversal fully implemented and tested by the mid-project check-in.