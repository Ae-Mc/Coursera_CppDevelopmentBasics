#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
    vector<string> result;
    auto prevIt = s.begin();
    auto it = find(begin(s), end(s), ' ');
    while (it != s.end()) {
        result.push_back({prevIt, it});
        prevIt = it + 1;
        it = find(it + 1, end(s), ' ');
    }
    result.push_back({prevIt, it});
    return result;
}
