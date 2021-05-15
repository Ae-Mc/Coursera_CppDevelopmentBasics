#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

/*
class Person {
public:
  // Вы можете вставлять сюда различные реализации класса,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
  void ChangeFirstName(int year, const string& first_name) {
  }
  void ChangeLastName(int year, const string& last_name) {
  }
  string GetFullName(int year) {
  }
};
*/

void TestEmptyPerson() {
  Person p;
  AssertEqual(p.GetFullName(99999), "Incognito", to_string(__LINE__));
}

void TestPersonWithOnlyLastName() {
  Person p;
  p.ChangeLastName(2000, "2000");
  AssertEqual(p.GetFullName(99999), "2000 with unknown first name", to_string(__LINE__));
  AssertEqual(p.GetFullName(2000), "2000 with unknown first name", to_string(__LINE__));
  AssertEqual(p.GetFullName(2000), "2000 with unknown first name", to_string(__LINE__));
  AssertEqual(p.GetFullName(1000), "Incognito", to_string(__LINE__));
  AssertEqual(p.GetFullName(1999), "Incognito", to_string(__LINE__));
}

void TestPersonWithOnlyFirstName() {
  Person p;
  p.ChangeFirstName(2000, "2000");
  AssertEqual(p.GetFullName(99999), "2000 with unknown last name", to_string(__LINE__));
  AssertEqual(p.GetFullName(2000), "2000 with unknown last name", to_string(__LINE__));
  AssertEqual(p.GetFullName(2000), "2000 with unknown last name", to_string(__LINE__));
  AssertEqual(p.GetFullName(1000), "Incognito", to_string(__LINE__));
  AssertEqual(p.GetFullName(1999), "Incognito", to_string(__LINE__));
}

void TestPersonWithMultipleChanges() {
  Person p;
  p.ChangeFirstName(1900, "first1");
  AssertEqual(p.GetFullName(9999), "first1 with unknown last name", to_string(__LINE__));
  p.ChangeLastName(1870, "last1");
  AssertEqual(p.GetFullName(2000), "first1 last1", to_string(__LINE__));
  p.ChangeLastName(1970, "last2");
  AssertEqual(p.GetFullName(2000), "first1 last2", to_string(__LINE__));
  AssertEqual(p.GetFullName(1969), "first1 last1", to_string(__LINE__));
  p.ChangeFirstName(1980, "first2");
  AssertEqual(p.GetFullName(1981), "first2 last2", to_string(__LINE__));
  AssertEqual(p.GetFullName(1972), "first1 last2", to_string(__LINE__));
}

int main() {
  TestRunner runner;
  runner.RunTest(TestEmptyPerson, "TestEmptyPerson");
  runner.RunTest(TestPersonWithOnlyFirstName, "TestPersonWithOnlyFirstName");
  runner.RunTest(TestPersonWithOnlyLastName, "TestPersonWithOnlyLastName");
  runner.RunTest(TestPersonWithMultipleChanges, "TestPersonWithMultipleChanges");
  return 0;
}
