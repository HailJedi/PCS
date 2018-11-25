#include <bits/stdc++.h>

using namespace std;

const int N = 2048;
const int M = N * N;

inline int readInt() {
  int n = 0, ch = getchar();
  while (!isdigit(ch)) ch = getchar();
  while (isdigit(ch)) n = n * 10 + ch - '0', ch = getchar();
  return n;
}

struct Edge {
  Edge *next;
  bool is_bi;
  int u, v;
  void *operator new(size_t, Edge *next, int u, int v, bool is_bi) {
    static Edge pool[M*2], *p = pool;
    if (p == pool + M*2) {
      p = pool;
    }
    Edge *ret = p++;
    ret->next = next;
    ret->u = u;
    ret->v = v;
    ret->is_bi = is_bi;
    return ret;
  }
} *head[N];

void add_edge(int u, int v, bool b) {
  head[u] = new (head[u], u, v, b) Edge;
}

int dfn[N], low[N];
int dt;

void dfs(int u, int f) {
  dfn[u] = low[u] = ++dt;
  for (Edge *e = head[u]; e; e = e->next) {
    int v = e->v;
    if (!dfn[v]) {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (e->is_bi) {
        if (low[v] > dfn[u]) {
          printf("%d %d 2\n", u, v);
        } else {
          printf("%d %d 1\n", u, v);
        }
      }
    } else 
    if (dfn[v] < dfn[u] && v != f) {
      low[u] = min(low[u], dfn[v]);
      if (e->is_bi) {
        printf("%d %d 1\n", u, v);
      }
    }
  }
}

int main() {
//  freopen("read", "r", stdin);
//  freopen("write", "w", stdout);
  
  int n, m;
  while (scanf("%d %d", &n, &m) == 2) {
    memset(head, 0x0, sizeof head);
    for (int i = 1; i <= m; i++) {
      int u, v, b;
 //     scanf("%d %d %d", &u, &v, &b);
      u = readInt(), v = readInt(), b = readInt();
      if (b == 2) {
        add_edge(u, v, true);
        add_edge(v, u, true);
      } else {
        add_edge(u, v, false);
      }
    }
    memset(dfn, 0, sizeof dfn);
    dt = 0;
    for (int u = 1; u <= n; u++) {
      if (!dfn[u]) {
        dfs(u, -1);
      }
    }
  }
  return 0;
}

