
# CS225 Final Project
Team name: 11:59  
Airport and Flight Data: [OpenFlights](https://openflights.org/data.html)

Project in general: Our projects makes use of the openflights dataset and the airports and routes between them. Using this dataset, we wanted to create two main functions: determining the shortest path between two airports, determining the most popular airports in the world. 

Github Organization:
 - Datasets: Our full dataset is located in the data folder titled "airports.dat" and "routes.dat". 
 - Header files: The header files for our project is located in our includes folder. "heap.hpp" is for our heap implementation, "airport.hpp" is our airport struct and everything an airport node includes, "flightgraph.hpp" contains all our functions from the constructor to our algorithm implementations.
 - Cpp files: Our cpp files are located in our src folder. "heap.cpp" is the methods of our heap implementation, "flightgraph.cpp" is the methods of all our functions. "main.cpp" is where we call all of our functions based on user input. 
 - Tests: We wrote all our tests in the tests folder under "tests.cpp". It contains all the testing we did for our functions. All of our functions have thorogh tests done to ensure their functionality.
 - Log: Our log is titled "LOG.md". It is located in our main directory.
 - Proposal: Our proposal is titled "PROPOSAL.md". It is located in our main directory.
 - Written Report: Our report is titled "RESULTS.md". It is located in our main directory.
 - Presentation: Our presentation is titled "WHATEVER WE CALL IT". It is located in our main directory.

Running Instructions:
Our program utilizes the terminal to interface with the user so they can use it. First, you must run "bin/airports" in terminal. You will be prompted with three different options for what dataset you want to use. You must input the corresponding number to what you want.
  1. Default dataset. This is the large dataset that encompasses majority of airports in the world.
  2. Test dataset. This is a much smaller scale version of our default dataset that we conducted tests on throughout our project.
  3. Custom dataset. This will prompt you to give a custom dataset of your choosing. It must match the format and you should write the file directory for where it is located.
<br>
You will then be asked which operation you want to execute. Again, choose the number corresponding to the function you want to run.
<br>
<br>
  1. DFS traversal. You will be prompted for a starting point. You should input the IATA code of the desired airport and we will print a DFS traversal in one of two locations
  <br>   
     a. bin/dfs_output.txt. This will simply print the traversal to this file, which you can find in the bin folder. 
   <br>
     b. Somewhere else. You will be prompted to input a custom file path, where the output will be printed to.
   <br>
   <br>
  2. Shortest path between two airports. You will then be prompted on whether you want the shortest path based on minimum airports visited, or minimum distance traveled. You should input the number corresponding to your choice.
  <br>
   a. Least number of airports visited. In this case, you will be prompted for a departure airport followed by a destination airport. You should input the IATA codes for each airport. The result will be printed to the terminal.  
   <br>
   b. Least distance traveled. In this case, you will be prompted for a departure airport followed by a destination airport. You should input the IATA codes for each airport. The result will be printed to the terminal.
   <br>
   <br>
  3. Get a ranking of the most popular airports in the dataset. You will then be prompted to input how many of the top airports you would like to see. (ie. top 10 most popular, top 15 most popular, etc). You should input a whole number and the rankings will print to the terminal along with their corresponding "weight." This weight was calculated in our pagerank algorithm.
