#include "types.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

const auto toTuple(const Region &region) {
  return tie(region.std_name, region.parent_std_name, region.names,
             region.population);
}

namespace std {
template <> struct less<Region> {
  bool operator()(const Region &lhs, const Region &rhs) const {
    return toTuple(lhs) < toTuple(rhs);
  }
};
} // namespace std

int FindMaxRepetitionCount(const std::vector<Region> &regions) {
  std::map<Region, int> repetitions;
  for (const auto &region : regions) {
    if (repetitions.find(region) != repetitions.end()) {
      repetitions[region] += 1;
    } else {
      repetitions[region] = 1;
    }
  }

  if (repetitions.empty())
    return 0;
  return std::max_element(repetitions.begin(), repetitions.end(),
                          [](const std::pair<Region, int> &lhs,
                             const std::pair<Region, int> &rhs) {
                            return lhs.second < rhs.second;
                          })
      ->second;
}

int main() {
  std::cout
      << FindMaxRepetitionCount({
             {"Moscow",
              "Russia",
              {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
              89},
             {"Russia",
              "Eurasia",
              {{Lang::DE, "Russland"},
               {Lang::FR, "Russie"},
               {Lang::IT, "Russia"}},
              89},
             {"Moscow",
              "Russia",
              {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
              89},
             {"Moscow",
              "Russia",
              {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
              89},
             {"Russia",
              "Eurasia",
              {{Lang::DE, "Russland"},
               {Lang::FR, "Russie"},
               {Lang::IT, "Russia"}},
              89},
         })
      << std::endl;
}
