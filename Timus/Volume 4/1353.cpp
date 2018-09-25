#include <bits/stdc++.h>

using namespace std;

const int N = 10 + 1;
const int S = 81 + 1;

int f[N][S];

int main() {
  int s;
  cin >> s;
  for (int i = 0; i < 10; i++) {
    f[2][i] = 1;
  }
  for (int i = 2; i < 10; i++) {
    for (int j = 0; j <= s; j++) {
      for (int k = 0; k < 10; k++) {
        if (j + k <= s) {
          f[i+1][j+k] += f[i][j];
        }
      }
    }
  }
  cout << f[10][s] + (s == 1) << endl;
  return 0;
}
