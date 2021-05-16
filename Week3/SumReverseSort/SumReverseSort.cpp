#include "sum_reverse_sort.h"
#include <algorithm>

int Sum(int x, int y) {
    return x + y;
}

string Reverse(string s) {
    string reversed;
    reversed.resize(s.size());
    for(auto i = 0; i < s.size(); i++) {
        reversed[i] = s[s.size() - 1 - i];
    }
    return reversed;
}

void Sort(vector<int> &nums) {
    sort(nums.begin(), nums.end());
}
