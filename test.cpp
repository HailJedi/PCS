/*
Created 2018-11-10
"Convex Countour"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 2500 + 5;

int n;
double f[N][N][2];
bool vis[N][N][2];
double x[N], y[N];

double dist(int i, int j) {
  return sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));
}

int main() {
  freopen("test.in", "r", stdin);
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%lf %lf", &x[i], &y[i]);
  }
  for (int len = 1; len < n; len++) {
    for (int i = 0; i < n; i++) {
      int j1 = (i - len + n) % n;
      f[i][j1][1] = max(f[i][(j1+1)%n][1], dist(i, j1) + f[j1][(i-1+n)%n][0]);
      int j2 = (i + len) % n;
      f[i][j2][0] = max(f[i][(j2-1+n)%n][0], dist(i, j2) + f[j2][(i+1)%n][1]);
    }
  }
  double ans = 0;
  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    ans = max(ans, f[i][j][1]);
    j = (i - 1 + n) % n;
    ans = max(ans, f[i][j][0]);
  }
  printf("%.10lf\n", ans);
  return 0;
}
