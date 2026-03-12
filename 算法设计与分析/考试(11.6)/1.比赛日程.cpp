#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int M;
  cin >> M;

  int N = 1 << M;

  vector<vector<int>> a(N, vector<int>(N, 0));

  // base matrix for 2
  if (N >= 2) {
    a[0][0] = 1;
    a[0][1] = 2;
    a[1][0] = 2;
    a[1][1] = 1;
  } else {
    a[0][0] = 1;
  }

  for (int sz = 2; sz < N; sz <<= 1) {
    int half = sz;
    for (int i = 0; i < half; ++i) {
      for (int j = 0; j < half; ++j) {
        a[i][j + half] = a[i][j] + half; // top-right
        a[i + half][j] = a[i][j] + half; // bottom-left
        a[i + half][j + half] = a[i][j]; // bottom-right
      }
    }
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cout << a[i][j] << (j + 1 == N ? '\n' : ' ');
    }
  }

  return 0;
}