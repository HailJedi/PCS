#include <bits/stdc++.h>

using namespace std;

const int N = 10000 + 5;
const int M = 200 + 5;
const int INF = 0x3f3f3f3f;

int c[N];
int f[M][M];

void update(int &x, int y) {
  if (x > y) {
    x = y;
  }
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &c[i]);
  }
  memset(f, INF, sizeof f);
  for (int i = 2; i <= m; i++) {
    for (int j = 1; j < i; j++) {
      f[i][j] = c[i] + c[j];
    }
  }
  for (int j = 2; j < n; j++) {
    int stk = INF;
    for (int i = min(n, j+m-1); i > m && i > j; i--) {
      update(stk, f[j%M][(i-m)%M]);
      f[i%M][j%M] = stk + c[i];
    }
  }
  int ans = INF;
  for (int i = 0; i < m-1 && n-i >= 2; i++) {
    for (int j = i+1; j < m && n-j >= 1; j++) {
      update(ans, f[(n-i)%M][(n-j)%M]);
    }
  }
  printf("%d\n", ans);
  return 0;
}
