/*
Created 2018-11-04
"Karen and Supermarket"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 5000 + 5;
const long long INF = 0x3f3f3f3f3f3f3f3f;

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
}

long long f[N][N][2]; // ith, take j, take self
int c[N], d[N];
int sz[N];

void update(long long &x, long long y) {
  if (x > y) {
    x = y;
  }
}

void dfs(int u) {
  sz[u] = 1;
  f[u][0][0] = 0;
  f[u][1][0] = c[u];
  f[u][1][1] = c[u] - d[u];
  for (Edge *e = head[u]; e; e = e->next) {
    dfs(e->v);
    for (int i = sz[u]; ~i; i--) {
      for (int j = sz[e->v]; ~j; j--) {
        update(f[u][i+j][1], f[u][i][1] + min(f[e->v][j][0], f[e->v][j][1]));
        update(f[u][i+j][0], f[u][i][0] + f[e->v][j][0]);
      }
    }
    sz[u] += sz[e->v];
  }
}

int main() {
  int n, b;
  scanf("%d %d", &n, &b);
  scanf("%d %d", &c[1], &d[1]);
  for (int i = 2; i <= n; i++) {
    int p;
    scanf("%d %d %d", &c[i], &d[i], &p);
    add_edge(p, i);
  }
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      f[i][j][0] = f[i][j][1] = INF;
    }
  }
  dfs(1);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (f[1][i][0] <= b || f[1][i][1] <= b) {
      ans = i;
    }
  }
  printf("%d\n", ans);
  return 0;
}
