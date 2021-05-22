#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>

using namespace std;

template<typename T>
vector<vector<T>> GetPermutations(const vector<T>& basePermutation) {
    vector<vector<T>> result{basePermutation};
    vector<T> currentPermutation = basePermutation;
    while(prev_permutation(currentPermutation.begin(), currentPermutation.end())) {
        result.push_back(currentPermutation);
    }
    return result;
}

int main() {
    int N;
    cin >> N;
    vector<int> v(N);
    for(int i = N; i > 0; i--) {
        v[N - i] = i;
    }
    auto permutations = GetPermutations(v);
    for(const auto& permutation : permutations) {
        copy(begin(permutation), end(permutation), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
}
