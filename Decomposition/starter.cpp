#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

template<class T> 
istream& operator>>(istream& is, vector<T>& v) {
  for(auto& e : v) {
    is >> e;
  }
  return is;
}

template<class T> 
ostream& operator<<(ostream& os, const vector<T>& v) {
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

istream& operator>>(istream& is, Query& q) {
  string operation_code;
  is >> operation_code;
  if (operation_code == "NEW_BUS") {
    q.type = QueryType::NewBus;
    is >> q.bus;
    int stop_count;
    is >> stop_count;
    q.stops.resize(stop_count);
    is >> q.stops;
  } else if (operation_code == "BUSES_FOR_STOP") {
    q.type = QueryType::BusesForStop;
    is >> q.stop;
  } else if (operation_code == "STOPS_FOR_BUS") {
    q.type = QueryType::StopsForBus;
    is >> q.bus;
  } else if (operation_code == "ALL_BUSES") {
    q.type = QueryType::AllBuses;
  }
  return is;
}

struct BusesForStopResponse {
  vector<string> buses_for_stop;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
  if (r.buses_for_stop.empty()) {
    return os << "No stop";
  }
  os << r.buses_for_stop;
  return os;
}

struct StopsForBusResponse {
  vector<pair<string, vector<string>>> stops_for_bus;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (r.stops_for_bus.empty()) {
    return os << "No bus";
  }
  bool isFirst = true;
  for(const auto& [stop, busses] : r.stops_for_bus) {
    if (isFirst) {
      isFirst = false;
    } else {
      os << endl;
    }
    os << "Stop " << stop << ": ";
    if (busses.size() == 0) {
      os << "no interchange" << endl;
    } else {
      os << busses;
    }
  }
  return os;
}

struct AllBusesResponse {
  map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (r.buses_to_stops.empty()) {
    os << "No buses";
  } else {
    bool isFirst = true;
    for (const auto& bus_item : r.buses_to_stops) {
      if (isFirst) {
        isFirst = false;
      } else {
        os << endl;
      }
      os << "Bus " << bus_item.first << ": ";
      for (const string& stop : bus_item.second) {
        os << stop << " ";
      }
    }
  }
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;
    for(const auto& stop : stops) {
      stops_to_buses[stop].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    if (stops_to_buses.count(stop) == 0) {
      return {};
    }
    return {stops_to_buses.at(stop)};
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    StopsForBusResponse r;
    if (buses_to_stops.count(bus) > 0) {
      for (const string& stop : buses_to_stops.at(bus)) {
        r.stops_for_bus.push_back({stop, {}});
        if (stops_to_buses.at(stop).size() > 1) {
          for (const string& other_bus : stops_to_buses.at(stop)) {
            if (bus != other_bus) {
              r.stops_for_bus.back().second.push_back(other_bus);
            }
          }
        }
      }
    }
    return r;
  }

  AllBusesResponse GetAllBuses() const {
    return {buses_to_stops};
  }
private:
  map<string, vector<string>> buses_to_stops;
  map<string, vector<string>> stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
