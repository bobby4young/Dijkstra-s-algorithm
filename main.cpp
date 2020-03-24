#include "string"
#include "graph.h"
#include <iostream>

bool VERBOSE = true;

int main (int argc, char** argv) {
  std::string input_file = "input.txt";
  if (argc == 2) {
    input_file = argv[1];
  }

  Graph graph(input_file);
  graph.getRouteDistance(1, "A-B-C");
  graph.getRouteDistance(2, "A-D");
  graph.getRouteDistance(3, "A-D-C");
  graph.getRouteDistance(4, "A-E-B-C-D");
  graph.getRouteDistance(5, "A-E-D");

  graph.getNTripsWithMaxNSTOP(6, "C-C", 3);
  graph.getNTripsWithNSTOP(7, "A-C", 4);
  graph.getNTripsWithNSTOP(7, "A-C", 4);

  graph.getLengthOfShortestRoute(8, "A-C");
  graph.getLengthOfShortestRoute(9, "B-B");

  graph.getNRoutesBetweenTwoCitiesWithMaxDistance(10, "C-C", 30);
  
  std::cout << std::endl << "------------extension---------------------" << std::endl;
  graph.getRouteDuration(1, "A-B-C");
  graph.getRouteDuration(2, "A-D");
  graph.getRouteDuration(3, "A-D-C");
  graph.getRouteDuration(4, "A-E-B-C-D");
  graph.getRouteDuration(5, "A-E-D");

  graph.getNTripsWithMaxDuration(6, "C-C", 30);
  graph.getNTripsWithDuration(7, "A-C", 30);

  graph.getDurationOfQuickestRoute(8, "A-C");
  graph.getDurationOfQuickestRoute(9, "B-B");
  graph.getNRoutesBetweenTwoCitiesWithMaxDuration(10, "C-C", 35);

  return 0;
}
