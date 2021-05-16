#pragma once

#include <string>
#include <utility>
#include <vector>
#include <map>
#include <ostream>

struct BusesForStopResponse {
  std::vector<std::string> buses_for_stop;
};

std::ostream& operator<<(std::ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
  std::vector<std::pair<std::string, std::vector<std::string>>> stops_for_bus;
};

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
  std::map<std::string, std::vector<std::string>> buses_to_stops;
};

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);

