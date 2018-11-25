#include <bits/stdc++.h>

using namespace std;

const int N = 300 + 5;
const int INF = 0x3f3f3f3f;

struct Circle {
  int x, y, r, e;
  Circle() {}
  void read() {
    scanf("%d %d %d %d", &x, &y, &r, &e);
  }
} *circle[N];

struct Edge {
  Edge *next;
  int u, v;
  void *operator new(size_t, Edge *next, int u, int v) {
    static Edge pool[N*N*100], *p = pool;
    if (p == pool + N*N*100) {
      p = pool;
    }
    Edge *ret = p++;
    ret->next = next;
    ret->u = u;
    ret->v = v;
    return ret;
  }
} *head[N], *scc_head[N];

void add_edge(Edge **head, int u, int v) {
  head[u] = new (head[u], u, v) Edge;
}

int dfn[N], low[N], dt;
int stk[N], tp;
int scc_no[N], sc;

void dfs(int u) {
  dfn[u] = low[u] = ++dt;
  stk[++tp] = u;
  for (Edge *e = head[u]; e; e = e->next) {
    int v = e->v; 
    if (!dfn[v]) {
      dfs(v);
      low[u] = min(low[u], low[v]);
    } else
    if (!scc_no[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (dfn[u] == low[u]) {
    sc++;
    while (tp) {
      int x = stk[tp--];
      scc_no[x] = sc;
      if (x == u) {
        break;
      }
    }
  }
}

int val[N], obj[N];
bool take[N], in[N], vis[N];
int amt, sum;

void dfs2(int u) {
  vis[u] = true;
  for (Edge *e = scc_head[u]; e; e = e->next) {
    if (!vis[e->v]) {
      dfs2(e->v);
    }
  }
  if (take[u]) {
    printf(" %d", obj[u]);
  }
}

int main() {
//  freopen("read", "r", stdin);
//  freopen("write", "w", stdout);
   
  for (int i = 0; i < N; i++) {
    circle[i] = new Circle();
  }
  int T, kase = 0;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
      circle[i]->read();
    }
    memset(head, 0x0, sizeof head);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) if (i != j) {
        if (pow(circle[i]->e + circle[i]->r + circle[j]->r, 2) 
           >= pow(circle[i]->x-circle[j]->x, 2) 
              + pow(circle[i]->y-circle[j]->y, 2)) {
          add_edge(head, i, j);
        }
      }
    }
    memset(scc_no, 0, sizeof scc_no);
    memset(dfn, 0, sizeof dfn);
    dt = sc = tp = 0;
    for (int i = 0; i < n; i++) {
      if (!dfn[i]) {
        dfs(i);
      }
    }
    memset(scc_head, 0x0, sizeof scc_head);
    memset(in, false, sizeof in);
    memset(val, INF, sizeof val);
    for (int u = 0; u < n; u++) {
      int u_scc = scc_no[u];
      if (val[u_scc] > circle[u]->e) {
        val[u_scc] = circle[u]->e;
        obj[u_scc] = u;
      }
      for (Edge *e = head[u]; e; e = e->next) {
        int v_scc = scc_no[e->v];
        if (u_scc != v_scc) {
          add_edge(scc_head, u_scc, v_scc);
          in[v_scc] = true;
        }
      }
    }
    memset(take, false, sizeof take);
    printf("Case #%d:", ++kase);
    amt = sum = 0;
    vector< pair<int, int> > candi;
    for (int i = 1; i <= sc; i++) {
      if (!in[i]) {
        amt++;
        sum += val[i];
        take[i] = true;
      } else {
        candi.push_back(make_pair(val[i], i));
      }
    }
    sort(candi.begin(), candi.end());
    for (int i = 0; i < candi.size(); i++) {
      int va = candi[i].first, id = candi[i].second;
      if ((sum+va)*amt < sum*(amt+1)) {
        sum += va;
        amt ++;
        take[id] = true;
      } else {
        break;
      }
    }
    memset(vis, false, sizeof vis);
    for (int i = sc; i >= 1; i--) {
      if (!in[i]) {
        dfs2(i);
      }
    }
    printf("\n");
  }
  return 0;
}
