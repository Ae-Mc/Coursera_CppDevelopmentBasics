#include <map>
#include <iostream>
#include <stdexcept>

template<class Key, class Value>
Value& GetRefStrict(std::map<Key, Value>& m, const Key& key) {
  if(m.find(key) == m.end())
    throw std::runtime_error("Key not found");
  return m[key];
}

int main() {
  using namespace std;
  map<int, string> m = {{0, "value"}};
  string& item = GetRefStrict(m, 0);
  item = "newvalue";
  cout << m[0] << endl; // выведет newvalue
}
