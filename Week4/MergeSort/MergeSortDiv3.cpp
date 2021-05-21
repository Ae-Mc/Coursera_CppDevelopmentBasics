#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>

using namespace std;
template<typename RandomIt>
void MergeSort(RandomIt rangeBegin, RandomIt rangeEnd) {
    if (rangeEnd - rangeBegin < 2) {
        return;
    }
    vector<typename RandomIt::value_type> v(rangeBegin, rangeEnd);
    vector<typename RandomIt::value_type> temp;
    MergeSort(begin(v),
            begin(v) + (end(v) - begin(v)) / 3);
    MergeSort(begin(v) + (end(v) - begin(v)) / 3,
            begin(v) + (end(v) - begin(v)) * 2 / 3);
    MergeSort(begin(v) + (end(v) - begin(v)) * 2 / 3,
            end(v));

    merge(
            begin(v),
            begin(v) + (end(v) - begin(v)) / 3,
            begin(v) + (end(v) - begin(v)) / 3,
            begin(v) + (end(v) - begin(v)) * 2 / 3,
            back_inserter(temp));
    merge(
            begin(temp),
            end(temp),
            begin(v) + (end(v) - begin(v)) * 2 / 3,
            end(v),
            rangeBegin);
}

/*
int main() {
    vector<int> v{9, 1,3,4,6,2,1,3,4};
    MergeSort(begin(v), end(v));
    for (auto x : v) {
        cout << x << ' ';
    }
    cout << endl;
    return 0;
}
*/
