/*
Created 2018-10-06
"Split the Tree"
A greedy solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int up[N];
int dep[N], path[N];
int fa[N][21];
int n, L;
int w[N];
long long S;
long long sumw[N];
vector<int> g[N];

void prepare(int u, int f = 0) {
  dep[u] = dep[f] + 1;
  sumw[u] = sumw[f] + w[u];
  up[u] = u;
  fa[u][0] = f;
  for (int i = 1; i <= 20; i++) {
    fa[u][i] = fa[fa[u][i-1]][i-1];
  }
  int lim = L-1;
  for (int i = 20; i >= 0; i--) {
    if (fa[up[u]][i] != 0 && (1 << i) <= lim && sumw[u] - sumw[fa[fa[up[u]][i]][0]] <= S) {
      up[u] = fa[up[u]][i];
      lim -= (1 << i);
    }
  }
  for (int v: g[u]) {
    prepare(v, u);
  }
}

int solve(int u) {
  int ret = 0, best = -1;
  for (int v: g[u]) {
    ret += solve(v);
    if (path[v] != v) {
      if (best == -1 || dep[path[v]] < dep[best]) {
        best = path[v];
      }
    }
  }
  if (best == -1) {
    ret++;
    best = up[u];
  }
  path[u] = best;
  return ret;
}

int main() {
  scanf("%d %d %lld", &n, &L, &S);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &w[i]);
    if (w[i] > S) {
      printf("-1\n");
      return 0;
    }
  }
  for (int i = 2; i <= n; i++) {
    int p;
    scanf("%d", &p);
    g[p].push_back(i);
  }
  prepare(1);
  printf("%d\n", solve(1));
  return 0;
}
