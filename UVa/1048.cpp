#include <bits/stdc++.h>

using namespace std;

const int N = 20 + 2;
const int M = 10 + 2;
const int C = 400 + 2;
const int S = C * M;
const int INF = 0x3f3f3f3f;

struct Dijkstra {
  struct Edge {
    Edge *next;
    int u, v, w, id;
    void *operator new(size_t, Edge *next, int u, int v, int w, int id) {
      static Edge pool[S*S], *p = pool;
      if (p == pool + S*S) {
        p = pool;
      }
      Edge *ret = p++;
      ret->next = next;
      ret->u = u;
      ret->v = v;
      ret->w = w;
      ret->id = id;
      return ret;
    }
  } *head[S], *pre[S];

  struct State {
    int d, u;
    void *operator new(size_t, int d, int u) {
      static State pool[S*S], *p = pool;
      if (p == pool + S*S) {
        p = pool;
      }
      State *ret = p++;
      ret->d = d;
      ret->u = u;
      return ret;
    }
    bool operator < (const State *&s) const {
      return d > s->d;
    }
  };

  int dist[S];
  bool vis[S];
  
  void init() {
    memset(head, 0x0, sizeof head);
  }

  void add_edge(int u, int v, int w, int id) {
    head[u] = new (head[u], u, v, w, id) Edge;
  }

  int solve(int s, int t) {
    memset(dist, INF, sizeof dist);
    memset(vis, false, sizeof vis);
    dist[s] = 0;
    pre[s] = 0x0;
    priority_queue<State*> q;
    q.push(new (0, s) State);
    while (!q.empty()) {
      State *cur = q.top();
      q.pop();
      if (vis[cur->u]) {
        continue;
      }
      vis[cur->u] = true;
      if (cur->u == t) {
        break;
      }
      for (Edge *e = head[cur->u]; e; e = e->next) {
        if (dist[e->v] > dist[cur->u] + e->w) {
          dist[e->v] = dist[cur->u] + e->w;
          pre[e->v] = e;
          q.push(new (dist[e->v], e->v) State);
        }
      }
    }
    return dist[t];
  }

  void printPath(int u) {
    if (pre[u] == 0x0) {
      return;
    }
    printPath(pre[u]->u);
    printf(" %d", pre[u]->id);
  }
} solver;

vector<int> ticket[N], path[N];
int cost[N];

vector<int> idx;
int find(int x) {
  return lower_bound(idx.begin(), idx.end(), x) - idx.begin();
}

int id[S][M], d;
int ID(int x, int y) {
  return id[x][y] != -1 ? id[x][y] : id[x][y] = ++d;
}

int main() {
//  freopen("read", "r", stdin);
//  freopen("write", "w", stdout);

  int kase = 1;
  int n, m, k;
  while (scanf("%d", &n) == 1 && n) {
    d = -1;
    memset(id, -1, sizeof id);
    idx.clear();
    for (int i = 1; i <= n; i++) {
      scanf("%d %d", &cost[i], &k);
      ticket[i] = vector<int>(k, 0);
      for (int j = 0; j < k; j++) {
        scanf("%d", &ticket[i][j]);
        idx.push_back(ticket[i][j]);
      }
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
      scanf("%d", &k);
      path[i] = vector<int>(k, 0);
      for (int j = 0; j < k; j++) {
        scanf("%d", &path[i][j]);
        idx.push_back(path[i][j]);
      }
    }
    sort(idx.begin(), idx.end());
    unique(idx.begin(), idx.end());
    for (int i = 1; i <= m; i++) {
      solver.init();
      for (int j = 1; j <= n; j++) {
        int s = find(ticket[j][0]);
        for (int k = 0; k < path[i].size(); k++) {
          int p = k;
          for (int l = 1; l < ticket[j].size(); l++) {
            int e = find(ticket[j][l]);
            if (e == find(path[i][p])) {
              p++;
            }
            solver.add_edge(ID(s, k), ID(e, p), cost[j], j);
            if (p == path[i].size()) {
              break;
            }
          }
        }
      }
      int s = ID(find(path[i][0]), 1);
      int e = ID(find(path[i].back()), path[i].size());
      printf("Case %d, Trip %d: ", kase, i);
      printf("Cost = %d\n", solver.solve(s, e));
      printf("  Tickets used:");
      solver.printPath(e);
      printf("\n");
    }
    kase++;
  }
  return 0;
}
