#include <bits/stdc++.h>

using namespace std;

const int N = 250 + 5;
const int W = 1000 + 5;
const long long INF = 0x3f3f3f3f3f3f3f3f;

int n, w;
int tl[N], wt[N];

void update(long long &x, long long y) {
  if (x < y) {
    x = y;
  }
}

long long f[2][W];

bool check(int x) {
  int t = 0;
  memset(f[t], -INF, sizeof f[t]);
  f[t][0] = 0;
  for (int i = 1; i <= n; i++) {
    memset(f[t^1], -INF, sizeof f[t^1]);
    for (int j = 0; j <= w; j++) {
      if (f[t][j] != -1) {
        update(f[t^1][j], f[t][j]);
        update(f[t^1][min(j+wt[i], w)], f[t][j] + 1LL * 1000 * tl[i] - 1LL * x * wt[i]);
      }
    }
    t ^= 1;
  }
  return f[t][w] >= 0;
}

int main() {
  freopen("talent.in", "r", stdin);
  freopen("talent.out", "w", stdout);
  scanf("%d %d", &n, &w);
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &wt[i], &tl[i]);
  }
  int l = 0, r = N * W * W;
  while (r - l > 1) {
    int mid = (l + r) / 2;
    if (check(mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }
  printf("%d\n", l);
  return 0;
}
