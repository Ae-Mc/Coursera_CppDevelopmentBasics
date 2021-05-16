#include "bus_manager.h"

void BusManager::AddBus(const std::string& bus, const std::vector<std::string>& stops) {
    buses_to_stops[bus] = stops;
    for(const auto& stop : stops) {
      stops_to_buses[stop].push_back(bus);
    }
  }

BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) const {
  if (stops_to_buses.count(stop) == 0) {
    return {};
  }
  return {stops_to_buses.at(stop)};
}

StopsForBusResponse BusManager::GetStopsForBus(const std::string& bus) const {
  StopsForBusResponse r;
  if (buses_to_stops.count(bus) > 0) {
    for (const std::string& stop : buses_to_stops.at(bus)) {
      r.stops_for_bus.push_back({stop, {}});
      if (stops_to_buses.at(stop).size() > 1) {
        for (const std::string& other_bus : stops_to_buses.at(stop)) {
          if (bus != other_bus) {
            r.stops_for_bus.back().second.push_back(other_bus);
          }
        }
      }
    }
  }
  return r;
}

AllBusesResponse BusManager::GetAllBuses() const {
  return {buses_to_stops};
}
