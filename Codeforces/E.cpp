/*
Created 2018-09-28 09:32
Codeforces Round #199 (Div.2) E. Xenia and Tree
http://codeforces.com/contest/342/problem/E
A centroid decomposition solution
（WA test#3）
*/
#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const int INF = 0x3f3f3f3f;

int n, q;
vector<int> g[N];
bool vis[N];
int link[N], dist[N];
int sz[N], dep[N], fa[N][21];
int tot_num;

void dfs(int u, int f, bool ok = false) {
  sz[u] = 1;
  if (ok) {
    dep[u] = dep[f] + 1;
    fa[u][0] = f;
  }
  for (int i = 0; i < (int)g[u].size(); i++) {
    int v = g[u][i];
    if (v != f && !vis[v]) {
      dfs(v, u, ok);
      sz[u] += sz[v];
    }
  }
}

int dfs2(int u, int f) {
  for (int i = 0; i < (int)g[u].size(); i++) {
    int v = g[u][i];
    if (v != f && !vis[v]) {
      if (sz[v] * 2 >= tot_num) {
        return dfs2(v, u);
      }
    }
  }
  return u;
}

int find_lca(int u, int v) {
  if (dep[u] < dep[v]) {
    swap(u, v);
  }
  for (int i = 20; i >= 0; i--) {
    if (dep[fa[u][i]] >= dep[v]) {
      u = fa[u][i];
    }
  }
  if (u == v) {
    return u;
  }
  for (int i = 20; i >= 0; i--) {
    if (fa[u][i] != fa[v][i]) {
      u = fa[u][i];
      v = fa[v][i];
    }
  }
  return fa[u][0];
}

int root;
int ans[N];

void paint(int u) {
  int dis = 0;
  for (int v = u; v; v = link[v]) {
    ans[v] = min(ans[v], dis);
    dis += dist[v];
  }
}

int query(int u) {
  int ret = INF, dis = 0;
  for (int v = u; v; v = link[v]) {
    ret = min(ret, ans[v] + dis);
    dis += dist[v];
  }
  return ret;
}

int main() {
  // freopen("read.in", "r", stdin);
  scanf("%d %d", &n, &q);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1, 0, true);
  for (int i = 1; i <= 20; i++) {
    for (int j = 1; j <= n; j++) {
      fa[j][i] = fa[fa[j][i-1]][i-1];
    }
  }
  tot_num = sz[1];
  root = dfs2(1, 0);
  vis[root] = true;
  queue<int> que;
  que.push(root);
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    for (int i = 0; i < (int)g[u].size(); i++) {
      int v = g[u][i];
      if (!vis[v]) {
        dfs(v, u);
        tot_num = sz[v];
        int w = dfs2(v, u);
        vis[w] = true;
        int lca = find_lca(w, u);
        dist[w] = dep[w] + dep[u] - dep[lca] * 2;
        link[w] = u;
        que.push(w);
      }
    }
  }
  memset(ans, INF, sizeof ans);
  paint(1);
  while (q--) {
    int t, v;
    scanf("%d %d", &t, &v);
    if (t == 1) {
      paint(v);
    } else {
      printf("%d\n", query(v));
    }
  }
  return 0;
}
