/*
Created 2018-11-04
"Tree"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 3000 + 5;
const int INF = 0x3f3f3f3f;

int f[N][N][3];

struct Edge {
  Edge *next;
  int v, w;
  void *operator new(size_t, Edge *next, int v, int w) {
    static Edge pool[N*2], *p = pool;
    Edge *ret = p++;
    ret->next = next;
    ret->v = v;
    ret->w = w;
    return ret;
  }
} *head[N];

void add_edge(int u, int v, int w) {
  head[u] = new (head[u], v, w) Edge;
  head[v] = new (head[v], u, w) Edge;
}

void update(int &x, int y) {
  if (x > y) {
    x = y;
  }
}

int sz[N];

void dfs(int u, int fa) {
  sz[u] = 1;
  f[u][0][0] = f[u][0][1] = 0;
  for (Edge *e = head[u]; e; e = e->next) {
    if (e->v != fa) {
      dfs(e->v, u);
      for (int i = sz[u]-1; ~i; i--) {
        for (int j = sz[e->v]-1; ~j; j--) {
          for (int k = 2; ~k; k--) {
            for (int l = k; ~l; l--) {
              update(f[u][i+j+1][k], f[u][i][k-l] + f[e->v][j][l] + e->w * (2 - (l & 1)));
            }
          }
        }
      }
      sz[u] += sz[e->v];
    }
  }
}

int main() {
  int n, K;
  scanf("%d %d", &n, &K);
  for (int i = 1; i < n; i++) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    add_edge(u, v, w);
  }
  memset(f, INF, sizeof f);
  dfs(1, 0);
  int ans = INF;
  for (int i = 1; i <= n; i++) {
    for (int k = 0; k < 3; k++) {
      update(ans, f[i][K-1][k]);
    }
  }
  printf("%d\n", ans);
  return 0;
}
