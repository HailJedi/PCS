#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;
const int V = 1000 + 5;

int f[N][N*V];
int pre[N][N*V];
int w[N];

void dfs(int i, int W) {
  if (i) {
    dfs(i-1, pre[i][W]);
    if (pre[i][W] == W) {
      printf("%d ", i);
    }
  }
}

int main() {
  int W, n;
  scanf("%d", &W);
  if (W >= V * N) {
    printf("0\n");
    return 0;
  }
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &w[i]);
  }
  f[0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= W; j++) {
      if (f[i][j]) {
        f[i+1][j] += f[i][j];
        pre[i+1][j] = j;
        if (j+w[i+1] <= W) {
          f[i+1][j+w[i+1]] += f[i][j];
          pre[i+1][j+w[i+1]] = j;
        }
      }
    }
  }
  if (f[n][W] > 1) {
    printf("-1\n");
  } else
  if (f[n][W] == 0) {
    printf("0\n");
  } else {
    dfs(n, W);
    printf("\n");
  }
  return 0;
}
