#include <bits/stdc++.h>

using namespace std;

const int N = 10000 + 5;
const int M = 1000 + 5;

bool f[N][M];
int pre[N][M];
bool use[N][M];
int a[N];
int n, m;

void dfs(int i, int j) {
  if (i) {
    dfs(i-1, pre[i][j]);
    if (use[i][j]) {
      printf("%d ", i);
    }
  }
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    a[i] %= m;
  }
  f[1][1] = true;
  f[1][a[1]] = true;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (f[i][j]) {
        if (!f[i+1][j]) {
          f[i+1][j] |= f[i][j];
          pre[i+1][j] = j;
          use[i+1][j] = false;
        }
        if (!f[i+1][j*a[i+1]%m]) {
          f[i+1][j*a[i+1]%m] |= f[i][j];
          pre[i+1][j*a[i+1]%m] = j;
          use[i+1][j*a[i+1]%m] = true;
        }
      }
    }
  }
  for (int j = m-1; j >= 1; j--) {
    if (f[n][j]) {
      printf("%d\n", j);
      dfs(n, j);
      printf("\n");
      return 0;
    }
  }
  assert(false);
  return 0;
}
