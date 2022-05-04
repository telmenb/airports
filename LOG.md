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

---

### Week 3 - April 13th (Anish Sabnis)

Our objective this week was to complete the constructor and complete the DFS traversal. 

Over the week, in the nodes, we have added the adjency list and the weights using the Haversine formula. We found the Haversine formula online and formed that into a function to get the weights. I worked to complete this portion of the project, while Telmen began working on the DFS formula. As our team has shrunk, we are both helping each other out on all parts of the project. Thankfully, we were able to complete both goals.

The biggest roadblock we encountered was our team shrinking in half. This has made us work much harder in order to accomplish our goals. We still believe we will be able to complete all our goals. Another issue we encountered while working on the DFS algorithm is we were using a queue, but we quickly realized this and fixed it. We found this after doing a manual DFS and seeing the output not including all the nodes.

Next week, we hope to complete Djikstra's algorithm. We saw it during lecture and hope to use it to help us.

---

### Week 4 - April 22nd (Telmen Bayarsaikhan)

Our main objective this week was to start progress on the shortest path algorithms. Initially, we had hoped to complete both the BFS shortest path and Dijkstra's algorithm together by the end, but unfortunately we were only able to finish BFS.

Anish and I got together and pair-programmed the function. We used a simple Breadth-First Search in tandem with a hashmap to keep track of previously visited airports for backtracking purposes.

The biggest hurdle was not configuring the hashmap properly and resetting its previous airports. We had to change it so if an airport already had an entry in the map, we would skip over it.

Next week's main tasks are writing comprehensive tests for the BFS shortest path, as well as finishing Dijkstra's algorithm.

---

### Week 5 - April 27th (Anish Sabnis)

The main objective for this week was to finish Dijkstra's algorithm and write comprehensive tests for the BFS shortest path. We were able to accomplish close to 80% of our goals and successfully moved on to make progress on PageRank.

We worked together in implementing Dijkstra's algorithm, which required a minimum-priority queue. We copied over material from lab_heaps and repurposed it according to our needs, and wrote test cases to ensure proper functionality. Using the pseudocode provided in lecture, we were able to get an implementation working that had correct behaviour for 4/5 cases. I also moved on to stub out the GetRanking() method with our expected implementation this week.

Dijkstra's algorithm is still buggy with a path from Willard Airport in Champaign to JFK in NYC taking Dallas Fort-Worth, instead of O'Hare as its path. We thought the bug was in our heap implementation not working correctly, but after writing tests to verify proper behaviour, we are still a bit lost as to where the bug is.

Next week's goals are to test, polish, and finalize Dijkstra's and PageRank. We are also hoping to implement our UI by May 5th.

---

### Week 6 - May 4th (Telmen Bayarsaikhan)

Our main goals for this week were to finish up our project in its entirety. We fixed the bug in Dijkstra's algorithm, implemented PageRank, and wrote some tests, as well as a simple UI for our users.

Our Dijkstra's algorithm implementation had a small bug in which it did not work as expected in certain cases. We found this out to be caused by us popping the priority queue too early (before adding potential path neighbors). Now it is working as intended. For PageRank, we were able to find a [great resource](https://towardsdatascience.com/pagerank-3c568a7d2332) on the internet, with a thorough explanation and example of an implementation in python. We were able to adapt it into our project and now it is working as expected on both our full dataset and small test dataset. We also implemented a simplistic UI for users to work with. We later made changes to certain components to allow users the ability to define custom file paths for data and/or outputs (as stated in the requirements). Other than such, we've written simple test cases showcasing the correct behaviour of our graph functions.

After figuring out the bug in Dijkstra's algorithm, we've had close to no hurdles in our development. There was a small bug in the ClearCount() method where we were accessing counts by value and not by reference, thus not allowing us to run two graph operations back-to-back as at the start of the second operation, all nodes were already marked as visited. This was only used for testing purposes as users are not allowed to perform several graph operations on a single instance of FlightGraph.

Now our goals are to finish up and polish our project for grading. This might include writing more comprehensive tests for the last two graph functions, as well as work on our final presentation.