#include <bits/stdc++.h>

using namespace std;

const int N = 50000 + 5;
const int K = 300 + 5;
const int MOD = 1e9 + 7;

int f[2][2][K];

int main() {
  int n, rst[2];
  cin >> n >> rst[0] >> rst[1];
  int t = 1;
  f[t][0][1] = f[t][1][1] = 1;
  for (int i = 1; i < n; i++) {
    memset(f[t^1], 0, sizeof f[t^1]);
    for (int a = 0; a < 2; a++) {
      for (int j = 1; j <= rst[a]; j++) {
        (f[t^1][a^1][1] += f[t][a][j]) %= MOD;
        (f[t^1][a][j+1] += f[t][a][j]) %= MOD;
      }
    }
    t ^= 1;
  }
  int ans = 0;
  for (int a = 0; a < 2; a++) {
    for (int i = 1; i <= rst[a]; i++) {
      (ans += f[t][a][i]) %= MOD;
    }
  }
  cout << ans << endl;
  return 0;
}
