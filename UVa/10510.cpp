#include <bits/stdc++.h>

using namespace std;

const int N = 10000 + 5;

struct Edge {
  Edge *next;
  int u, v, f;
   void *operator new(size_t, Edge *next, int u, int v) {
    static Edge pool[N*2], *p = pool;
    if (p == pool + N*2) {
      p = pool;
    }
    Edge *ret = p++;
    ret->next = next;
    ret->u = u;
    ret->v = v;
    ret->f = 0;
    return ret;
  }
} *head[N];

void add_edge(int u, int v) {
  head[u] = new (head[u], u, v) Edge;
}

Edge *stk[N];
int tp;
int s[N];
int int_tp;
int dfn[N], low[N];
int dt;
int scc_no[N], sc;

bool dfs(int u) {
  dfn[u] = low[u] = ++dt;
  s[++int_tp] = u;
  for (Edge *e = head[u]; e; e = e->next) {
    int v = e->v;
    stk[++tp] = e;
    if (!dfn[v]) {
      if (!dfs(v)) {
        return false;
      }
      low[u] = min(low[u], low[v]);
    } else { 
      if (dfn[v] < dfn[u]) {
        for (int pt = tp; pt; pt--) {
          Edge *x = stk[pt];
          if (x->f) {
            return false;
          }
          x->f = 1;
          if (x->u == v) {
            break;
          }
        }
      }
      if (!scc_no[v]) {
        low[u] = min(low[u], dfn[v]);
      }
    }
    tp--;
  }
  if (low[u] == dfn[u]) {
    sc++;
    if (sc > 1) {
      return false;
    }
    while (int_tp) {
      int x = s[int_tp--];
      scc_no[x] = sc;
      if (x == u) {
        break;
      }
    }
  }
  return true;
}

int main() {
//  freopen("read", "r", stdin);
//  freopen("write", "w", stdout);
    
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m;
    scanf("%d %d", &n, &m);
    memset(head, 0x0, sizeof head);
    for (int i = 0; i < m; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      add_edge(u, v);
    }
    bool ok = true;
    memset(dfn, 0, sizeof dfn);
    memset(scc_no, 0, sizeof scc_no);
    dt = tp = sc = 0;
    for (int i = 0; i < n && ok; i++) {
      if (!dfn[i]) {
        ok &= dfs(i);
      }
    }
    printf("%s\n", ok ? "YES" : "NO");
  }
  return 0;
}
