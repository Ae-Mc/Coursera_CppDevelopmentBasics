#include <vector>
#include <set>

using namespace std;

template<typename T>
void RemoveDuplicates(vector<T>& v) {
    set<T> s(begin(v), end(v));
    v = vector<T>(begin(s), end(s));
}
