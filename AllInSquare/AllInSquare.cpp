#include <vector>
#include <map>
#include <utility>
#include <sstream>
#include <iostream>

// template<typename First, typename Second>
// std::ostream& operator<<(std::ostream& out, const std::pair<First, Second>& p);
template<typename T>
std::vector<T> Sqr(std::vector<T> v);
template<typename Key, typename Value> std::map<Key, Value>
Sqr(std::map<Key, Value> m);
template<typename First, typename Second> std::pair<First, Second>
Sqr(std::pair<First, Second> p);
template<typename T>
T Sqr(T x);

template<typename T>
T Sqr(T x) {
  return x * x;
}

template<typename T>
std::vector<T> Sqr(std::vector<T> v) {
  for (T& x : v) {
    x = Sqr(x);
  }
  return v;
}

template<typename Key, typename Value> std::map<Key, Value>
Sqr(std::map<Key, Value> m) {
  for (auto& x : m) {
    x.second = Sqr(x.second);
  }
  return m;
}

template<typename First, typename Second> std::pair<First, Second>
Sqr(std::pair<First, Second> p) {
  p.first = Sqr(p.first);
  p.second = Sqr(p.second);
  return p;
}

/*
template<typename Collection>
std::string JoinCollection(const Collection& collection, std::string separator = ", ") {
  std::stringstream ss;
  bool isFirst = true;
  for(const auto& x : collection) {
    if (isFirst) {
      isFirst = false;
    } else {
      ss << separator;
    }
    ss << x;
  }
  return ss.str();
}

template<typename First, typename Second>
std::ostream& operator<<(std::ostream& out, const std::pair<First, Second>& p) {
  return out << '(' << p.first << ", " << p.second << ')';
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
  return out << '[' << JoinCollection(v) << ']';
}

template<typename Key, typename Value>
std::ostream& operator<<(std::ostream& out, const std::map<Key, Value>& m) {
  return out << '{' << JoinCollection(m) << '}';
}
*/


int main() {
  /*
  std::cout << Sqr(20.5) << std::endl;
  std::cout << Sqr(std::vector<int>{10, 11, 12}) << std::endl;
  std::cout << Sqr(std::map<char, double>{{'a', 47}, {'b', 48}}) << std::endl;
  std::cout << Sqr(std::make_pair(100.0, 25)) << std::endl;
  */
  // Пример вызова функции
  using namespace std;
  vector<int> v = {1, 2, 3};
  cout << "vector:";
  for (int x : Sqr(v)) {
    cout << ' ' << x;
  }
  cout << endl;

  map<int, pair<int, int>> map_of_pairs = {
    {4, {2, 2}},
    {7, {4, 3}}
  };
  cout << "map of pairs:" << endl;
  for (const auto& x : Sqr(map_of_pairs)) {
    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
  }
}
