#include <bits/stdc++.h>

using namespace std;

const int N = 10;

int n, m;
long long f[N][1<<N];

void dfs(int x, int k, int last, int now, int b1, int b2) {
  if (k == m) {
    if (!b1 && !b2) {
      f[x][now] += f[x-1][last];
    }
    return;
  }
  if (!b1 && !b2) {
    dfs(x, k+1, last << 1, now << 1 | 1, 0, 0);
    dfs(x, k+1, last << 1, now << 1 | 1, 1, 0);
    dfs(x, k+1, last << 1, now << 1 | 1, 0, 1);
  }
  if (!b1) {
    dfs(x, k+1, last << 1, now << 1 | b2, 1, 1);
  }
  if (!b2) {
    dfs(x, k+1, last << 1 | (b1 ^ 1), now << 1 | 1, 0, 1);
    dfs(x, k+1, last << 1 | (b1 ^ 1), now << 1 | 1, 1, 1);
  }
  dfs(x, k+1, last << 1 | (b1 ^ 1), now << 1 | b2, 0, 0);
}

int main() {
  scanf("%d %d", &n, &m);
  if (m > n) {
    swap(m, n);
  }
  int all = (1 << m) - 1;
  f[0][all] = 1;
  for (int i = 1; i <= n; i++) {
    dfs(i, 0, 0, 0, 0, 0);
  }
  printf("%lld\n", f[n][all]);
  return 0;
}
