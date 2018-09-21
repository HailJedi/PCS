#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
const double INF = 1e30;

double f[N][N];
bool cross[N][N];

void update(double &x, double y) {
  if (x > y) {
    x = y;
  }
}

int main() {
  int n, m, k;
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= k; i++) {
    int p, q;
    scanf("%d %d", &p, &q);
    cross[p-1][q-1] = true;
  }
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      f[i][j] = INF;
    }
  }
  f[0][0] = 0;
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      update(f[i][j+1], f[i][j] + 100);
      update(f[i+1][j], f[i][j] + 100);
      if (cross[i][j]) {
        update(f[i+1][j+1], f[i][j] + 100 * sqrt(2));
      }
    }
  }
  printf("%d\n", (int)round(f[n][m]));
  return 0;
}
