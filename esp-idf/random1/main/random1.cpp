#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;

extern "C" void app_main(void) {
  vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
  mt19937 rd(seed);

  for (int i = 0; i < 10; i++) {
    shuffle(v.begin(), v.end(), rd);
    for (auto &i : v)
      cout << i << " ";
    cout << endl;
  }
}
