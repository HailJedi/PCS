/*
Created 2018-11-04
"[Lydsy1710月赛]小A的树"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 5000 + 5;
const int INF = 0x3f3f3f3f;

int f[N][N], g[N][N];

struct Edge {
  Edge *next;
  int v;
  void *operator new(size_t, Edge *next, int v) {
    static Edge pool[N*2], *p = pool;
    if (p == pool + N*2) {
      p = pool;
    }
    Edge *ret = p++;
    ret->next = next;
    ret->v = v;
    return ret;
  }
} *head[N];

void add_edge(int u, int v) {
  head[u] = new (head[u], v) Edge;
  head[v] = new (head[v], u) Edge;
}

int n;
int b[N];
int sz[N];

void dfs(int u, int fa) {
  sz[u] = 1;
  f[u][0] = g[u][0] = 0;
  f[u][1] = g[u][1] = b[u];
  for (Edge *e = head[u]; e; e = e->next) {
    if (e->v != fa) {
      dfs(e->v, u);
      for (int i = sz[u]; i; i--) {
        for (int j = sz[e->v]; j; j--) {
          f[u][i+j] = min(f[u][i+j], f[u][i] + f[e->v][j]);
          g[u][i+j] = max(g[u][i+j], g[u][i] + g[e->v][j]);
        }
      }
      sz[u] += sz[e->v];
    }
  }
  for (int i = 0; i <= n; i++) {
    f[0][i] = min(f[0][i], f[u][i]);
    g[0][i] = max(g[0][i], g[u][i]);
  }
}

int main() {
  int T, q;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &q);
    memset(head, 0x0, sizeof head);
    for (int i = 1; i < n; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      add_edge(u, v);
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", &b[i]);
    }
    memset(f, INF, sizeof f);
    memset(g, -INF, sizeof g);
    dfs(1, 0);
    while (q--) {
      int x, y;
      scanf("%d %d", &x, &y);
      if (f[0][x] <= y && y <= g[0][x]) {
        puts("YES");
      } else {
        puts("NO");
      }
    }
    puts("");
  }
  return 0;
}
