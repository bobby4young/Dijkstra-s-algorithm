#include <iostream>
#include <fstream>
#include <limits>
#include <limits.h>
#include <list>
#include <string>
#include <sstream> // std::stringstream
#include <vector>
#include "graph.h"

extern bool VERBOSE;

template<class T>
void Print(T t) {
  if (VERBOSE) {
    std::cout << t << std::endl;
  }
}

template<class T>
void PrintNoNewLine(T t) {
  if (VERBOSE) {
    std::cout << t << " ";
  }
}

template<class T1, class T2>
void Print(T1 t1, T2 t2) {
    std::cout << t1 << " " << t2 << std::endl;
}
// template<class T>
// void Print(std::string string, T t) {
//   if (VERBOSE) {
//     std::cout << string << " " << t << std::endl;
//   }
// }

std::string EraseDelimiterFromString(std::string route, const std::string delimiter) {
  size_t pos = 0;
  while ((pos = route.find(delimiter)) != std::string::npos) {
    route.erase(pos, delimiter.length());
  }
  return route;
}

Graph::Graph(const std::string input_file) {
  std::ifstream myfile ("../" + input_file);
  if (myfile.is_open()) {
    std::string line;
    std::vector<std::string> string_array;
    char max = 'A';
    while (getline(myfile, line)) {
      Print("graph input", line);
      if (line.compare(0, 7,"Graph: ") == 0) {
       line.erase(0, 7);
      }
      std::stringstream string_stream(line);
      size_t pos = 0;
      std::string one_route;
      while (getline(string_stream, one_route, ' ')) {
        //one_connection = line.substr(0, pos);
        string_array.push_back(one_route);
        if (one_route.at(0) > max) {
          max = one_route.at(0);     
        }
        if (one_route.at(1) > max) {
          max = one_route.at(1);
        }
        line.erase(0, pos + 1);
      }
    }
    Print("max:", max);
    if (max > 'Z') {
      std::cout << "There is city with character: " << max << std::endl;
      exit(1);
    }
    int max_index = max - 'A';
    Print("max_index:", max_index);
    map_.resize(max_index + 1);
    for (auto& m: map_) {
      m.resize(max_index + 1);
    }
    for (auto route: string_array) {
      int first_character = route.at(0) - 'A';
      int second_character = route.at(1) - 'A';
      map_[first_character][second_character] = route.at(2) - '0';
    }
  }
  else {
    std::cout << "Unable to open file";
    exit(1);
  }
  for (auto m1: map_) {
    for (auto m2: m1) {
      PrintNoNewLine(m2);
    }
    Print("");  
  }
  boarding_time_ = 2;
}

int Graph::getRouteDistance(const int n_output, const std::string in_route) const {
  const std::string route = EraseDelimiterFromString(in_route, "-");
  if (route.length() < 2) {
    std::cout << "Output #" << n_output << ": needs at least two cities in route, instead input is " << in_route << std::endl;
    return INT_MIN;
  }
  std::vector<int> route_number;
  for (size_t i = 0; i < route.length(); i++) {
    route_number.push_back(route.at(i) - 'A');
  }
  int route_distance = 0;
  for (std::vector<int>::iterator it = route_number.begin(); it != (route_number.end() -1); it ++) {
    if (map_[*it][*(it + 1)] == 0 && (*it) != (*(it + 1))) {
      std::cout << "Output #" << n_output << ": NO SUCH ROUTE" << std::endl;
      return INT_MIN;
    }
    else {
      route_distance += map_[*it][*(it + 1)];
    }

  }
  std::cout << "Output #" << n_output << ": " << route_distance << std::endl;
  return route_distance;
}

int Graph::getNTripsWithNSTOP(const int n_output, const std::string in_route, const int n_stop) const {
  const std::string route = EraseDelimiterFromString(in_route, "-");
  if (route.length() != 2) {
    std::cout << "Output #" << n_output << ": needs two cities in route, instead input is " << in_route << std::endl;
    return INT_MIN;
  }
  int origin_index = route.at(0) - 'A';
  int destination_index = route.at(1) - 'A';

  std::vector< std::vector<int> > visited;
  visited.resize(n_stop + 1);
  for (auto& v: visited) {
    v.assign(map_.size(), 0);
  }
  visited[0][origin_index] = 1;
  for (int i = 1; i < n_stop + 1; i ++) {
    for (int j = 0; j < map_.size(); j ++) {
      if (visited[i-1][j] > 0) {
        for (int k = 0; k < map_.size(); k ++) {
          if (map_[j][k] > 0) {
            visited[i][k] += visited[i-1][j];
          }
        }
      }
    } 
  }
  for (auto v1: visited) {
    for (auto v2: v1) {
      PrintNoNewLine(v2);
    }
    PrintNoNewLine("");  
  }
  std::cout << "Output #" << n_output << ": " << visited[n_stop][destination_index] << std::endl;
  return visited[n_stop][destination_index];
}

int Graph::getNTripsWithMaxNSTOP(const int n_output, const std::string in_route, const int n_stop) const {
  const std::string route = EraseDelimiterFromString(in_route, "-");
  if (route.length() != 2) {
    std::cout << "Output #" << n_output << ": needs two cities in route, instead input is " << in_route << std::endl;
    return INT_MIN;
  }
  int origin_index = route.at(0) - 'A';
  int destination_index = route.at(1) - 'A';

  std::vector< std::vector<int> > visited;
  visited.resize(n_stop + 1);
  for (auto& v: visited) {
    v.assign(map_.size(), 0);
  }
  visited[0][origin_index] = 1;
  for (int i = 1; i < n_stop + 1; i ++) {
    for (int j = 0; j < map_.size(); j ++) {
      if (visited[i-1][j] > 0) {
        for (int k = 0; k < map_.size(); k ++) {
          if (map_[j][k] > 0) {
            visited[i][k] += visited[i-1][j];
          }
        }
      }
    } 
  }
  for (auto v1: visited) {
    for (auto v2: v1) {
      PrintNoNewLine(v2);
    }
    Print("");  
  }
  int n_trip = 0;
  for (int i = 1; i < visited.size(); i ++) {
    n_trip += visited[i][destination_index];
  }
  std::cout << "Output #" << n_output << ": " << n_trip << std::endl;
  return n_trip;
}

int Graph::getLengthOfShortestRoute(const int n_output, const std::string in_route) const {
  const std::string route = EraseDelimiterFromString(in_route, "-");
  if (route.length() != 2) {
    std::cout << "Output #" << n_output << ": needs two cities in route, instead input is " << in_route << std::endl;
    return INT_MIN;
  }
  int origin_index = route.at(0) - 'A';
  int destination_index = route.at(1) - 'A';

  // current min distance from origin to city
  std::vector<int> city_distance(map_.size(), INT_MAX);
  city_distance[origin_index] = 0;
  std::vector<bool> parsed_cities(map_.size(), false);

  // each iteration parses one city: min_city, which is the closest city among unparsed cities
  for (int i = 0; i < map_.size(); i ++) {
    int min_city;
    int min_distance = INT_MAX;
    for (int i = 0; i < map_.size(); i ++) {
      if (parsed_cities[i] == false && city_distance[i] <= min_distance) {
        min_distance = city_distance[i];
        min_city = i;
      }
    }
    Print("next closest city", min_city);
    parsed_cities[min_city] = true;
    for (int j = 0; j < map_.size(); j ++) {
      // from min_city to j city
      if (!parsed_cities[j] && map_[min_city][j] > 0 && city_distance[min_city] != INT_MAX &&
       city_distance[min_city] + map_[min_city][j] < city_distance[j]) {
        city_distance[j] = city_distance[min_city] + map_[min_city][j];
      }
    }
    if (i == 0) {
    // enables the route to return to the origin 
      parsed_cities[min_city] = false;
      city_distance[min_city] = INT_MAX;
    }
    PrintNoNewLine("Distance to cities: ");
    for (auto d: city_distance) {
      PrintNoNewLine(d);
    }
    Print("");
    if (parsed_cities[destination_index]) {
      // early break, once the path to destination is found 
      break;
    }
  }
  if (city_distance[destination_index] == INT_MAX) {
    std::cout << "Output #" << n_output << ": NO SUCH ROUTE" << std::endl;
  }
  else {
    std::cout << "Output #" << n_output << ": " << city_distance[destination_index] << std::endl;
  }
  return city_distance[destination_index];
}
// int Graph::getNRoutesBetweenTwoCitiesWithMaxDistance(const int n_output, const std::string in_route, const int max_distance) const {
//   const std::string route = EraseDelimiterFromString(in_route, "-");
//   if (route.length() != 2) {
//     std::cout << "Output #" << n_output << ": needs two cities in route, instead input is " << in_route << std::endl;
//     return INT_MIN;
//   }
//   int origin_index = route.at(0) - 'A';
//   int destination_index = route.at(1) - 'A';

//   int n_route = 0;
//   std::vector<std::vector<int> > former_trip_distance;
//   former_trip_distance.resize(map_.size());
//   former_trip_distance[origin_index].push_back(0);
//   bool is_trip_exists = true;
//   while (is_trip_exists) {
//     std::vector<std::vector<int> > trip_distance;
//     trip_distance.resize(map_.size());
//     is_trip_exists = false;

//     // each loop is one origin of this stop
//     for (int j = 0; j < map_.size(); j ++) {
//       if (former_trip_distance[j].size() > 0) {
//         for (int k = 0; k < map_.size(); k ++) {
//           if (map_[j][k] > 0) {
//             for (auto trip: former_trip_distance[j]) {
//               int distance = trip + map_[j][k];
//               if (distance < max_distance) {
//                 trip_distance[k].push_back(distance);
//                 is_trip_exists = true;
//               }
//             }
//           }
//         }
//       }
//     }
//     n_route += trip_distance[destination_index].size();
//     former_trip_distance = trip_distance;
//     int index = 0;
//     for (auto t1: trip_distance) {
//       PrintNoNewLine((char)('A' + index)); 
//       index ++;
//       for (auto t2: t1) {
//         Print(t2); 
//       }
//       Print("");
//     }
//   }
//   std::cout << "Output #" << n_output << ": " << n_route << std::endl;
//   return n_route;
// }
int Graph::getNRoutesBetweenTwoCitiesWithMaxDistance(const int n_output, const std::string in_route, const int max_distance) const {
  const std::string route = EraseDelimiterFromString(in_route, "-");
  if (route.length() != 2) {
    std::cout << "Output #" << n_output << ": needs two cities in route, instead input is " << in_route << std::endl;
    return INT_MIN;
  }
  int origin_index = route.at(0) - 'A';
  int destination_index = route.at(1) - 'A';

  int n_route = 0;
  std::list<int> former_trip_distance[map_.size()];
  former_trip_distance[origin_index].push_back(0);
  bool is_trip_exists = true;
  while (is_trip_exists) {
    std::list<int> trip_distance[map_.size()];
    is_trip_exists = false;

    // each loop is one origin of this stop
    for (int j = 0; j < map_.size(); j ++) {
      if (former_trip_distance[j].size() > 0) {
        for (int k = 0; k < map_.size(); k ++) {
          if (map_[j][k] > 0) {
            for (auto trip: former_trip_distance[j]) {
              int distance = trip + map_[j][k];
              if (distance < max_distance) {
                trip_distance[k].push_back(distance);
                is_trip_exists = true;
              }
            }
          }
        }
      }
    }
    n_route += trip_distance[destination_index].size();
    int trip_index = 0;
    for (auto t: trip_distance) {
      former_trip_distance[trip_index] = trip_distance[trip_index];
      trip_index++;
    }
    int index = 0;
    for (auto t1: trip_distance) {
      PrintNoNewLine((char)('A' + index)); 
      index ++;
      for (auto t2: t1) {
        Print(t2); 
      }
      Print("");
    }
  }
  std::cout << "Output #" << n_output << ": " << n_route << std::endl;
  return n_route;
}

int Graph::getRouteDuration(const int n_output, const std::string in_route) const {
  const std::string route = EraseDelimiterFromString(in_route, "-");
  if (route.length() < 2) {
    std::cout << "Output #" << n_output << ": needs at least two cities in route, instead input is " << in_route << std::endl;
    return INT_MIN;
  }
  std::vector<int> route_number;
  for (size_t i = 0; i < route.length(); i++) {
    route_number.push_back(route.at(i) - 'A');
  }
  int route_duration = 0;
  for (std::vector<int>::iterator it = route_number.begin(); it != (route_number.end() -1); it ++) {
    if (map_[*it][*(it + 1)] == 0 && (*it) != (*(it + 1))) {
      std::cout << "Output #" << n_output << ": NO SUCH ROUTE" << std::endl;
      return INT_MIN;
    }
    else {
      route_duration += map_[*it][*(it + 1)];
      route_duration += 2;
    }
  }
  // At last stop, don't need to pick up passengers
  route_duration -= 2;  
  std::cout << "Output #" << n_output << ": " << route_duration << std::endl;
  return route_duration;
}

int Graph::getNTripsWithDuration(const int n_output, const std::string in_route, const int fix_duration) const {
  const std::string route = EraseDelimiterFromString(in_route, "-");
  if (route.length() != 2) {
    std::cout << "Output #" << n_output << ": needs two cities in route, instead input is " << in_route << std::endl;
    return INT_MIN;
  }
  int origin_index = route.at(0) - 'A';
  int destination_index = route.at(1) - 'A';

  std::vector< std::vector<int> > former_trip_duration;
  former_trip_duration.resize(map_.size());
  former_trip_duration[origin_index].push_back(0);
  bool is_trip_exists = true;
  int n_trip = 0;
  /* 
  Assuming spending two minutes at every stop(including the last stop), same problem and same result as
  long as we increase the duration by two minutes
  (trips distance) + 2 * (n_stop - 1) <= max_duration same as (trips distance) + 2 * n_stop <= max_duration + 2
  */
  const int fix_duration_plus = fix_duration + boarding_time_; 
  while (is_trip_exists) {
    std::vector< std::vector<int> > trip_duration;
    trip_duration.resize(map_.size());
    is_trip_exists = false;
    // each loop is one origin of this stop
    for (int i = 0; i < map_.size(); i ++) {
      if (former_trip_duration[i].size() > 0) {
        for (int j = 0; j < map_.size(); j ++) {
          if (map_[i][j] > 0) {
            for (auto trip: former_trip_duration[i]) {
              int duration = trip + map_[i][j] + 2;
              if (duration < fix_duration_plus) {
                trip_duration[j].push_back(duration);
                is_trip_exists = true;
              }
              else if (j == destination_index && duration == fix_duration_plus) {
                n_trip ++;
              }
            }
          }
        }
      }
    }
    former_trip_duration = trip_duration;
    int index = 0;
    for (auto t1: trip_duration) {
      PrintNoNewLine((char)('A' + index)); 
      index ++;
      for (auto t2: t1) {
        Print(t2); 
      }
      Print("");
    }
  }
  std::cout << "Output #" << n_output << ": " << n_trip << std::endl;
  return n_trip;
}

int Graph::getNTripsWithMaxDuration(const int n_output, const std::string in_route, const int max_duration) const {
  const std::string route = EraseDelimiterFromString(in_route, "-");
  if (route.length() != 2) {
    std::cout << "Output #" << n_output << ": needs two cities in route, instead input is " << in_route << std::endl;
    return INT_MIN;
  }
  int origin_index = route.at(0) - 'A';
  int destination_index = route.at(1) - 'A';

  std::vector< std::vector<int> > former_trip_duration;
  former_trip_duration.resize(map_.size());
  former_trip_duration[origin_index].push_back(0);
  bool is_trip_exists = true;
  int n_trip = 0;
  /* 
  Assuming spending two minutes at every stop(including the last stop), same problem and same result as
  long as we increase the max duration by two minutes
  (trips distance) + 2 * (n_stop - 1) <= max_duration same as (trips distance) + 2 * n_stop <= max_duration + 2
  */
  const int max_duration_plus = max_duration + 2; 
  while (is_trip_exists) {
    std::vector< std::vector<int> > trip_duration;
    trip_duration.resize(map_.size());
    is_trip_exists = false;

    // each loop is one origin of this stop
    for (int i = 0; i < map_.size(); i ++) {
      if (former_trip_duration[i].size() > 0) {
        for (int j = 0; j < map_.size(); j ++) {
          if (map_[i][j] > 0) {
            for (auto trip: former_trip_duration[i]) {
              //int duration = trip + map_[i][j] + boarding_time;
              int duration = trip + map_[i][j] + 2;
              if (duration < max_duration_plus) {
                trip_duration[j].push_back(duration);
                is_trip_exists = true;
              }
              if (j == destination_index && duration <= max_duration_plus) {
                n_trip ++;
              }
            }
          }
        }
      }
    }
    former_trip_duration = trip_duration;
    int index = 0;
    for (auto t1: trip_duration) {
      PrintNoNewLine((char)('A' + index)); 
      index ++;
      for (auto t2: t1) {
        Print(t2); 
      }
      Print("");
    }
  }
  std::cout << "Output #" << n_output << ": " << n_trip << std::endl;
  return n_trip;
}

int Graph::getDurationOfQuickestRoute(const int n_output, const std::string in_route) const {
  const std::string route = EraseDelimiterFromString(in_route, "-");
  if (route.length() != 2) {
    std::cout << "Output #" << n_output << ": needs two cities in route, instead input is " << in_route << std::endl;
    return INT_MIN;
  }
  int origin_index = route.at(0) - 'A';
  int destination_index = route.at(1) - 'A';
  
  // current min distance from origin to city
  std::vector<int> city_duration(map_.size(), INT_MAX);
  city_duration[origin_index] = 0;
  std::vector<bool> parsed_cities(map_.size(), false);
  //initial the distance after first stop
  for (int i = 0; i < map_.size(); i ++) {
    if (map_[origin_index][i] > 0) {
      city_duration[i] = map_[origin_index][i];
    }
  }
  // each iteration parses one city: min_city, which is the closest city among unparsed cities
  for (int i = 0; i < map_.size(); i ++) {
    int min_city;
    int min_duration = INT_MAX;
    for (int i = 0; i < map_.size(); i ++) {
      if (parsed_cities[i] == false && city_duration[i] <= min_duration) {
        min_duration = city_duration[i];
        min_city = i;
      }
    }
    Print("next closest city", min_city);
    parsed_cities[min_city] = true;
    for (int j = 0; j < map_.size(); j ++) {
      // from min_city to j city
      if (!parsed_cities[j] && map_[min_city][j] > 0 && city_duration[min_city] != INT_MAX &&
       city_duration[min_city] + map_[min_city][j] < city_duration[j]) {
        city_duration[j] = city_duration[min_city] + map_[min_city][j] + boarding_time_;
      }
    }
    if (i == 0) {
      // enable the route to go back to origin 
      parsed_cities[min_city] = false;
      city_duration[min_city] = INT_MAX;
    }
    PrintNoNewLine("Duration to cities: ");
    for (auto d: city_duration) {
      PrintNoNewLine(d);
    }
    Print("");
    if (parsed_cities[destination_index]) {
      break;
    }
  }
  if (city_duration[destination_index] == INT_MAX) {
    std::cout << "Output #" << n_output << ": NO SUCH ROUTE" << std::endl;
  }
  else {
    std::cout << "Output #" << n_output << ": " << city_duration[destination_index] << std::endl;
  }
  return city_duration[destination_index];
}

int Graph::getNRoutesBetweenTwoCitiesWithMaxDuration(const int n_output, const std::string in_route, const int max_duration) const {
  const std::string route = EraseDelimiterFromString(in_route, "-");
  if (route.length() != 2) {
    std::cout << "Output #" << n_output << ": needs two cities in route, instead input is " << in_route << std::endl;
    return INT_MIN;
  }
  int origin_index = route.at(0) - 'A';
  int destination_index = route.at(1) - 'A';
  Print("origin_index", origin_index);
  Print("destination_index", destination_index);

  int n_route = 0;
  std::vector<std::vector<int> > former_trip_duration;
  std::vector<std::vector<int> > first_trip_duration;
  former_trip_duration.resize(map_.size());
  first_trip_duration.resize(map_.size());
  former_trip_duration[origin_index].push_back(0);
  bool is_trip_exists = false; 
  for (int i = 0; i < map_.size(); i ++) {
    if (map_[origin_index][i] > 0) {
      for (auto trip: former_trip_duration[origin_index]) {
        // if the trip ends here, no time spending on picking up passengers
        int duration = trip + map_[origin_index][i];
        if (duration < max_duration) {
          first_trip_duration[i].push_back(duration);
          is_trip_exists = true;
        }
      }
    }
  }
  former_trip_duration = first_trip_duration; 
  n_route += first_trip_duration[destination_index].size();
  while (is_trip_exists) {
    is_trip_exists = false;
    std::vector<std::vector<int> > trip_duration;
    trip_duration.resize(map_.size());
    // each loop is one origin of this stop
    for (int j = 0; j < map_.size(); j ++) {
      if (former_trip_duration[j].size() > 0) {
        for (int k = 0; k < map_.size(); k ++) {
          if (map_[j][k] > 0) {
            for (auto trip: former_trip_duration[j]) {
              int duration = trip + map_[j][k] + boarding_time_;
              if (duration < max_duration) {
                trip_duration[k].push_back(duration);
                is_trip_exists = true;
              }
            }
          }
        }
      }
    }
    n_route += trip_duration[destination_index].size();
    former_trip_duration = trip_duration;
  }
  if (n_route == 0) {
    std::cout << "Output #" << n_output << ": 0 NO SUCH ROUTE" << std::endl;
  }
  else {
    std::cout << "Output #" << n_output << ": " << n_route << std::endl;
  }
  return n_route;
}
