/*
Created 2018-10-01
Hyperspace Highways
A bfs solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const int M = 500000 + 5;
const int Q = 200000 + 5;

int n, m, q;
int dep[N], fa[N][21];
set<int> g[N];

int main() {
  // freopen("read.in", "r", stdin);
  scanf("%d %d %d", &n, &m, &q);
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    g[u].insert(v);
    g[v].insert(u);
  }
  queue<int> que;
  dep[1] = 1;
  que.push(1);
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    for (auto v: g[u]) {
      if (dep[v] == 0) {
        dep[v] = dep[u] + 1;
        fa[v][0] = u;
        for (int i = 1; i <= 20; i++) {
          fa[v][i] = fa[fa[v][i-1]][i-1];
        }
        que.push(v);
      }
    }
  }
  while (q--) {
    int u, v;
    scanf("%d %d", &u, &v);
    if (dep[u] < dep[v]) {
      swap(u, v);
    }
    int ans = 0;
    for (int i = 20; i >= 0; i--) {
      if (dep[fa[u][i]] >= dep[v]) {
        u = fa[u][i];
        ans += (1 << i);
      }
    }
    if (u == v) {
      printf("%d\n", ans);
      continue;
    }
    for (int i = 20; i >= 0; i--) {
      if (fa[u][i] != fa[v][i]) {
        u = fa[u][i];
        v = fa[v][i];
        ans += (1 << (i + 1));
      }
    }
    ans += g[u].count(v) ? 1 : 2;
    printf("%d\n", ans);
  }
  return 0;
}
