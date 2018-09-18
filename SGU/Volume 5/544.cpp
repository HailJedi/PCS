#include <bits/stdc++.h>

using namespace std;

const int N = 500 + 5;
const int MOD = 1e9+9;

long long f[2][N][N];

pair<int, int> lvl[2*N];

int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  if ((n ^ k) & 1) {
    printf("0\n");
    return 0;
  }
  for (int i = 0; i < n; i++) {
    scanf("%d", &lvl[i].first);
    lvl[i].second = 0;
  }
  for (int i = n; i < 2*n; i++) {
    scanf("%d", &lvl[i].first);
    lvl[i].second = 1;
  }
  sort(lvl, lvl+2*n);
  f[0][0][0] = 1;
  int win[2] = {0};
  for (int i = 0; i < 2*n; i++) {
    int t = i & 1;
    for (int j = 0; j <= n; j++) {
      for (int k = 0; k <= n; k++) {
        if (f[t][j][k]) {
          (f[t^1][j][k] += f[t][j][k]) %= MOD;
          if (lvl[i].second == 0) {
            if (win[1]-j-k >= 0) {
              (f[t^1][j+1][k] += f[t][j][k] * (win[1]-j-k)) %= MOD;
            }
          } else {
            if (win[0]-j-k >= 0) {
              (f[t^1][j][k+1] += f[t][j][k] * (win[0]-j-k)) %= MOD;
            }
          }
        }
      }
    }
    win[lvl[i].second]++;
    memset(f[t], 0, sizeof f[t]);
  }
  int w0 = (n + k) / 2, w1 = (n - k) / 2;
  printf("%lld\n", f[0][w0][w1]);
  return 0;
}
