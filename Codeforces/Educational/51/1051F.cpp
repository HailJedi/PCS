/*
Created 2018-09-29
F. The Shortest Statement
A shortest path solution
*/

#include <bits/stdc++.h>

using namespace std;

const long long INF = 0x3f3f3f3f3f3f3f3f;
const int N = 100000 + 5;
const int M = N + 50;

struct Edge {
  Edge *next, *rev;
  int u, v, w;
  bool mark;
  void *operator new(size_t, Edge *next, int u, int v, int w) {
    static Edge pool[M*2], *p = pool;
    Edge *ret = p++;
    ret->next = next;
    ret->u = u;
    ret->v = v;
    ret->w = w;
    ret->mark = false;
    return ret;
  }
} *head[N];

void add_edge(int u, int v, int w) {
  head[u] = new (head[u], u, v, w) Edge;
  head[v] = new (head[v], v, u, w) Edge;
  head[u]->rev = head[v];
  head[v]->rev = head[u];
}

int dep[N], fa[N][21];
long long dis[N];
bool vis[N];

void dfs(int u) {
  vis[u] = true;
  for (Edge *e = head[u]; e; e = e->next) {
    if (!vis[e->v]) {
      e->mark = e->rev->mark = true;
      dep[e->v] = dep[u] + 1;
      dis[e->v] = dis[u] + e->w;
      fa[e->v][0] = u;
      dfs(e->v);
    }
  }
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

int n, m;
int src;
long long dist[50][N];

void dijkstra(int s, int u) {
  for (int i = 1; i <= n; i++) {
    dist[s][i] = INF;
  }
  dist[s][u] = 0;
  priority_queue< pair<long long, int> > q;
  q.push(make_pair(dist[s][u], u));
  while (!q.empty()) {
    int u = q.top().second;
    q.pop();
    for (Edge *e = head[u]; e; e = e->next) {
      if (dist[s][e->v] > dist[s][u] + e->w) {
        dist[s][e->v] = dist[s][u] + e->w;
        q.push(make_pair(-dist[s][e->v], e->v));
      }
    }
  }
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    add_edge(u, v, w);
  }
  dep[1] = 1;
  dfs(1);
  for (int i = 1; i <= 20; i++) {
    for (int j = 1; j <= n; j++) {
      fa[j][i] = fa[fa[j][i-1]][i-1];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (Edge *e = head[i]; e; e = e->next) {
      if (!e->mark) {
        dijkstra(++src, e->u);
        e->mark = e->rev->mark = true;
      }
    }
  }
  int q;
  scanf("%d", &q);
  while (q--) {
    int u, v;
    scanf("%d %d", &u, &v);
    int lca = find_lca(u, v);
    long long ans = dis[u] + dis[v] - 2 * dis[lca];
    for (int i = 1; i <= src; i++) {
      ans = min(ans, dist[i][u] + dist[i][v]);
    }
    printf("%lld\n", ans);
  }
  return 0;
}
