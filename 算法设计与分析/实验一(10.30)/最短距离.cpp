#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<int> xs(n), ys(n);
  for (int i = 0; i < n; ++i) {
    cin >> xs[i] >> ys[i];
  }

  sort(xs.begin(), xs.end());
  sort(ys.begin(), ys.end());

  int mx = xs[n / 2];
  int my = ys[n / 2];

  long long total = 0;
  for (int i = 0; i < n; ++i) {
    total += llabs((long long)xs[i] - mx);
    total += llabs((long long)ys[i] - my);
  }

  cout << total << '\n';
  return 0;
}
