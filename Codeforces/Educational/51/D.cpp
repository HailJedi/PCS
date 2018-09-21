#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
const int MOD = 998244353;

int f[N][2*N][4];

void add(int &x, int y) {
  x = (long long)(x + y) % MOD;
}

int main() {
  int n, k;
  cin >> n >> k;
  f[1][1][0] = 1;
  f[1][1][3] = 1;
  f[1][2][1] = 1;
  f[1][2][2] = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= k; j++) {
      for (int k = 0; k < 4; k++) {
        if (f[i][j][k] != 0) {
          for (int s = 0; s < 4; s++) {
            int r1 = (k >> 1) ^ (s >> 1), r2 = (k & 1) ^ (s & 1);
            int nj = max(0, r1 + r2 - (s == 0 || s == 3));
            add(f[i+1][j+nj][s], f[i][j][k]);
          }
        }
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < 4; i++) {
    add(ans, f[n][k][i]);
  }
  cout << ans << endl;
  return 0;
}
