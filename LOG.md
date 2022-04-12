# Development Log

### Week 1 - March 30th (Anish Sabnis):

Design:  
We have decided to use a hashmap to store the pointers to the nodes of the airports for quick accessibility. The keys will be the airport three-letter code, and the value will be the pointer to the node of the airport. Some airports do not have three-letter codes, so we are going to ignore those. Our airport node will contain the ID, its name, long and lat, an adjacency list vector, and a bool that says if it has been visited or not. When we do our traversal, we need to ensure that we don’t revisit the same nodes, so we have this visited board to help us.  

We needed to make our graph weighted because we want to use Dijkstra's algorithm to find the shortest path between two nodes. We have decided to weigh the edges by the geographical distance between the two nodes. This can be done using the longitude and latitude points between them. So this algorithm will tell the user the shortest total geographical distance between the airports.  

We stubbed out dependencies and included catch2 testing, as well as made our makefile.  

---

### Week 2 - April 9th (Telmen Bayarsaikhan):

Our main objective for this week was to finalize our proposal with the necessary changes and get started on working on the project. We’ve successfully managed to get our proposal approved and finalized critical design aspects. We also started progressing on the graph structure constructor.  

After stubbing out the header files, Anish and I sat down together to work on the constructor. Utilizing file and string streams, we processed the airport data to turn them into nodes.  

We set goals for each other where I was supposed to start writing tests and Anish would try to process the routes data. We have not progressed very far since then, unfortunately.  

We are definitely hoping to pick up the pace on our project and sprint to complete the constructor, as well as DFS traversal the meet the mid-project check-in date.