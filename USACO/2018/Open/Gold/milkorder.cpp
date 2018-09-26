#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

struct Edge {
  int u, v, lim;
  Edge() {}
  Edge(int u, int v, int lim) : u(u), v(v), lim(lim) {}
  bool operator < (const Edge &e) const {
    return v > e.v;
  }
};

vector<Edge> g[N];

void add_edge(int u, int v, int lim) {
  g[u].push_back(Edge(u, v, lim));
}

int n, m;
bool vis[N], fn[N];

bool dfs(int u, int lim) {
  vis[u] = true;
  for (int i = 0; i < (int)g[u].size(); i++) {
    int v = g[u][i].v;
    if (g[u][i].lim <= lim) {
      if ((vis[v] && !fn[v]) || !dfs(v, lim)) {
        return false;
      }
    }
  }
  fn[u] = true;
  return true;
}

bool check(int lim) {
  memset(vis, false, sizeof vis);
  memset(fn, false, sizeof fn);
  for (int i = 1; i <= n; i++) {
    if (!vis[i] && !dfs(i, lim)) {
      return false;
    }
  }
  return true;
}

int in[N];

int main() {
  freopen("milkorder.in", "r", stdin);
  freopen("milkorder.out", "w", stdout);
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int k;
    scanf("%d", &k);
    vector<int> vec;
    while (k--) {
      int u;
      scanf("%d", &u);
      vec.push_back(u);
    }
    for (int j = 0; j < (int)vec.size()-1; j++) {
      add_edge(vec[j], vec[j+1], i);
    }
  }
  for (int i = 1; i <= n; i++) {
    sort(g[i].begin(), g[i].end());
  }
  int l = 0, r = m+1;
  while (r - l > 1) {
    int mid = (l + r) / 2;
    if (check(mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < (int)g[i].size(); j++) {
      if (g[i][j].lim <= l) {
        in[g[i][j].v]++;
      }
    }
  }
  priority_queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (!in[i]) {
      q.push(-i);
    }
  }
  vector<int> ans;
  while (!q.empty()) {
    int u = -q.top();
    q.pop();
    ans.push_back(u);
    for (int i = 0; i < (int)g[u].size(); i++) {
      if (g[u][i].lim <= l) {
        if ((--in[g[u][i].v]) == 0) {
          q.push(-g[u][i].v);
        }
      }
    }
  }
  for (int i = 0; i < (int)ans.size()-1; i++) {
    printf("%d ", ans[i]);
  }
  printf("%d\n", ans.back());
  return 0;
}
