#include <bits/stdc++.h>

using namespace std;

const int N = 25;

char pat[N];
int bit[N];
int ans;
int n, m;

void dfs(int d, int row, int cov) {
  if (cov > ans) {
    return;
  }
  if (d == n) {
    if (__builtin_popcount(row) <= cov) {
      ans = min(ans, cov);
    }
  } else {
    dfs(d+1, row | bit[d], cov);
    dfs(d+1, row, cov+1);
  }
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%s", pat);
    for (int j = 0; j < m; j++) {
      bit[i] |= ((pat[j] == '*') << j);
    }
  }
  ans = N;
  dfs(0, 0, 0);
  printf("%d\n", ans);
  return 0;
}
