#include <bits/stdc++.h>

using namespace std;

const int N = 500 + 5;
const int INF = 0x3f3f3f3f;

int f[N][N];
int zsum[N], osum[N];

void update(int &x, int y) {
  if (x > y) {
    x = y;
  }
}

int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; i++) {
    int c;
    scanf("%d", &c);
    zsum[i] = zsum[i-1] + (c == 0);
    osum[i] = osum[i-1] + (c == 1);
  }
  memset(f, INF, sizeof f);
  f[0][0] = 0;
  for (int i = 1; i <= k; i++) {
    for (int j = i; j <= n; j++) {
      for (int k = i-1; k < j; k++) {
        update(f[i][j], f[i-1][k] + (zsum[j]-zsum[k]) * (osum[j]-osum[k]));
      }
    }
  }
  printf("%d\n", f[k][n]);
  return 0;
}
