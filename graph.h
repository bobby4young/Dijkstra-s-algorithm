#ifndef CODE_THE_FUTURE_GRAPH_H_
#define CODE_THE_FUTURE_GRAPH_H_

#include <iostream>
#include <fstream>
#include <limits>
#include <limits.h>
#include <string>
#include <sstream> // std::stringstream
#include <vector>

class Graph {
 public:
  Graph(const std::string input_file);
  int getRouteDistance(const int n_output, const std::string route) const;
  int getNTripsWithNSTOP(const int n_output, const std::string route, const int n_stops) const;
  int getNTripsWithMaxNSTOP(const int n_output, const std::string route, const int n_stops) const;
  int getLengthOfShortestRoute(const int n_output, const std::string route) const;
  int getNRoutesBetweenTwoCitiesWithMaxDistance(const int n_output, const std::string route, const int max_distance) const;
  
  // extension
  int getRouteDuration(const int n_output, const std::string route) const;
  int getNTripsWithDuration(const int n_output, const std::string route, const int duration) const;
  int getNTripsWithMaxDuration(const int n_output, const std::string route, const int max_duration) const;
  int getDurationOfQuickestRoute(const int n_output, const std::string route) const;
  int getNRoutesBetweenTwoCitiesWithMaxDuration(const int n_output, const std::string route, const int max_duration) const;
 private:
  std::vector<std::vector<int> > map_;
  // time spend at each stop to pick up passengers
  int boarding_time_;
};

#endif
