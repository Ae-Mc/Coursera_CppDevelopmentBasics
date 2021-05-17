#include <iostream>
#include <vector>
#include <set>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
    vector<T> result;
    auto it = elements.begin();
    for(; it != elements.end(); it++) {
        if (*it > border) {
            break;
        }
    }
    return vector<T>(it, elements.end());
}
