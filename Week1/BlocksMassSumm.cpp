#include <cstdint>
#include <iostream>

using namespace std;

int main() {
  uint32_t N, p;
  cin >> N >> p;
  uint64_t summ = 0;
  uint64_t W, H, D;
  for (; N > 0; N--) {
    cin >> W >> H >> D;
    summ += W * H * D * p;
  }
  cout << summ << endl;
  return 0;
}
