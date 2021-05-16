#include "responses.h"

template<class T> 
std::ostream& PrintVector(std::ostream& os, const std::vector<T>& v) {
  bool isFirst = true;
  for(auto& e : v) {
    if (!isFirst) {
      os << " ";
    } else {
      isFirst = false;
    }
    os << e;
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const BusesForStopResponse& r) {
  if (r.buses_for_stop.empty()) {
    return os << "No stop";
  }
  PrintVector(os, r.buses_for_stop);
  return os;
}

std::ostream& operator<<(std::ostream& os, const StopsForBusResponse& r) {
  if (r.stops_for_bus.empty()) {
    return os << "No bus";
  }
  bool isFirst = true;
  for(const auto& [stop, busses] : r.stops_for_bus) {
    if (isFirst) {
      isFirst = false;
    } else {
      os << std::endl;
    }
    os << "Stop " << stop << ": ";
    if (busses.size() == 0) {
      os << "no interchange";
    } else {
      PrintVector(os, busses);
    }
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const AllBusesResponse& r) {
  if (r.buses_to_stops.empty()) {
    os << "No buses";
  } else {
    bool isFirst = true;
    for (const auto& bus_item : r.buses_to_stops) {
      if (isFirst) {
        isFirst = false;
      } else {
        os << std::endl;
      }
      os << "Bus " << bus_item.first << ": ";
      for (const std::string& stop : bus_item.second) {
        os << stop << " ";
      }
    }
  }
  return os;
}

