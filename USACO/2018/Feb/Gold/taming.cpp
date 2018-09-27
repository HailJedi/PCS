#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;

int n;
int lg[N];
int f[2][N][N];

void update(int &x, int y) {
  if (x == -1 || x > y) {
    x = y;
  }
}

int main() {
  freopen("taming.in", "r", stdin);
  freopen("taming.out", "w", stdout);
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &lg[i]);
  }
  int t = 0;
  memset(f[t], -1, sizeof f[t]);
  f[t][1][0] = (lg[1] != 0);
  for (int i = 1; i < n; i++) {
    memset(f[t^1], -1, sizeof f[t^1]);
    for (int j = 0; j <= n; j++) {
      for (int k = 0; k <= n; k++) {
        if (f[t][j][k] != -1) {
          update(f[t^1][j][k+1], f[t][j][k] + (lg[i+1] != k+1));
          update(f[t^1][j+1][0], f[t][j][k] + (lg[i+1] != 0));
        }
      }
    }
    t ^= 1;
  }
  for (int i = 1; i <= n; i++) {
    int ans = 1e9;
    for (int j = 0; j <= n; j++) {
      if (f[t][i][j] != -1) {
        update(ans, f[t][i][j]);
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
