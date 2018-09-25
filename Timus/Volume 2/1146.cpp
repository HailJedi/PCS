#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;

int sum[N][N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int num;
      scanf("%d", &num);
      sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + num;
    }
  }
  int ans = -1e9;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 0; k < i; k++) {
        for (int l = 0; l < j; l++) {
          ans = max(ans, sum[i][j] - sum[k][j] - sum[i][l] + sum[k][l]);
        }
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}

