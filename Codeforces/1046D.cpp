/*
Created 2018-10-02
Interstellar battle
A probability problem
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int n, q;
double p[N], f[N];
vector<int> g[N];
int fa[N];

void dfs(int u) {
  for (auto v: g[u]) {
    if (v != fa[u]) {
      fa[v] = u;
      f[u] += p[v];
      dfs(v);
    }
  }
}

int main() {
  // freopen("read.in", "r", stdin);
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lf", &p[i]);
    p[i] = 1.0 - p[i];
  }
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    u++, v++;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1);
  double ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += (p[i] - p[i] * f[i]);
  }
  scanf("%d", &q);
  while (q--) {
    int u;
    double c;
    scanf("%d %lf", &u, &c);
    u++;
    ans -= (p[u] - p[u] * f[u] + p[fa[u]] - p[fa[u]] * f[fa[u]]);
    f[fa[u]] -= p[u];
    p[u] = 1.0 - c;
    f[fa[u]] += p[u];
    ans += (p[u] - p[u] * f[u] + p[fa[u]] - p[fa[u]] * f[fa[u]]);
    printf("%.5lf\n", ans);
  }
  return 0;
}
