Graph is a c++ class for realising graph search funtions.

-------------------------
Design
-------------------------
To realize the required search functions, two major algorithms are implemented in class graph:  
1. Breadth-first search  https://en.wikipedia.org/wiki/Breadth-first_search
2. Dijkstra algorithm  https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

Assuming n cities in the graph, a n dimensional diagonal matrix serves as a map. A number in i-th
row and j-th colume is the distance from i city to j city. Diatance zero means no route between 
those two cities. This matrix enables random access to distance data and check the existence of a
route. No bounds checking of city names in input txt file. Assuming they are all first few uppercase
letters in the alphabet.

Breadth-first search is implemented in the following methods:
  getRouteDistance
  getNTripsWithNSTOP
  getNTripsWithMaxNSTOP
  getNRoutesBetweenTwoCitiesWithMaxDistance
  getRouteDuration
  getNTripsWithDuration
  getNTripsWithMaxDuration
  getNRoutesBetweenTwoCitiesWithMaxDuration

Dijkstra algorithm is implemented in the following methods:
  getLengthOfShortestRoute
  getDurationOfQuickestRoute

The first input parameter of all the mothods is the output index, which will be shown in terminal. 
Second input parameter is the requir route in string witha '-' between city names. No bounds checking
of city names in input parameter. Assuming they are all first few uppercase letters in the alphabet.

When setting the global parameter VERBOSE in 'main.cpp' to true, the search steps will be printed to
the terminal. 
Comments in the code show the details of implementaion.

----------------------
How to compile
----------------------
-- navigate to the 'build' folder under 'CY_C++'.
-- Type 'cmake ../' in 'build/' to generate Makefiles. 
-- Type 'make' in 'build/' to compile the code. This will generate runnable graph.

----------------------
How to run
----------------------
Example1:  "./graph"
In folder 'build', type "./graph". This will take the default route in file 'input.txt' as routes in
graph and compute all the required functions in task and extension task.

Example2:  "./graph new_input_graph.txt"
In folder 'build', type "./graph new_input_graph.txt". This will pass a new txt file(*.txt) as routes in
graph and compute all the same required functions in task and extension task. No bounds checking
of city names in functions input parameter. Might need to change the route in function call if the new 
text file doesn't contain as many cities as the default input.txt.

-------------------------
License
-------------------------
MIT License

Copyright (c) 2019 CY

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
