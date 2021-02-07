#include <iostream>
#include <vector>

using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> temps(N);
  long double summ = 0;
  for(auto &temp: temps) {
    cin >> temp;
    summ += temp;
  }
  long double average = summ / temps.size();
  vector<int> aboveAverage;
  for(int i = 0; i < N; i++) {
    if (temps[i] > average)
      aboveAverage.push_back(i);
  }

  cout << aboveAverage.size() << endl;
  for (const auto& day : aboveAverage)
    cout << day << ' ';
  cout << endl;
  return 0;
}
