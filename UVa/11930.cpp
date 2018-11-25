#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
const int S = N * 2;

struct TwoSAT {
  struct Edge {
    Edge *next; 
    int u, v;
    void *operator new(size_t, Edge *next, int u, int v) {
      static Edge pool[N*N*5], *p = pool;
      if (p == pool + N*N*5) {
        p = pool;
      }
      Edge *ret = p++;
      ret->next = next;
      ret->u = u;
      ret->v = v;
      return ret;
    }
  };

  void add_edge(int u, int v) {
    head[u] = new (head[u], u, v) Edge;
  }
  
  int n;
  Edge *head[S];
  bool mark[S];
  int stk[S], tp;
  
  void init(int n) {
    this->n = n;
    memset(mark, false, sizeof mark);
    memset(head, 0x0, sizeof head);
  }
  
  bool dfs(int u) {
    if (mark[u^1]) {
      return false;
    }
    if (mark[u]) {
      return true;
    }
    mark[u] = true;
    stk[++tp] = u;
    for (Edge *e = head[u]; e; e = e->next) {
      if (!dfs(e->v)) {
        return false;
      }
    }
    return true;
  }

  void add_clause(int x, int xv, int y, int yv) {
    x = x * 2 + xv;
    y = y * 2 + xv;
    add_edge(x^1, y);
    add_edge(y^1, x);
  }
  
  bool solve() {
    for (int i = 0; i < 2*n; i += 2) {
      if (!mark[i] && !mark[i^1]) {
        tp = 0;
        if (!dfs(i)) {
          while (tp) {
            mark[stk[tp--]] = false;
          }
          if (!dfs(i^1)) {
            return false;
          }
        }
      }
    }
    return true;
  }
} solver;

struct Point {
  int x, y;
  Point() {}
  Point(int x, int y) : x(x), y(y) {}
  void read() {
    scanf("%d %d", &x, &y);
  }
  Point operator - (const Point &p2) const {
    return Point(x-p2.x, y-p2.y);
  }
} p[N][4];

int cross(const Point &p1, const Point &p2) {
  return p1.x * p2.y - p1.y * p2.x;
}

bool intersect(Point &p00, Point &p01, Point &p10, Point &p11) {
  int c1 = cross(p00-p01,p10-p01), c2 = cross(p00-p01,p11-p01),
        c3 = cross(p11-p10, p00-p10), c4 = cross(p11-p10, p01-p10);
  return c1 * c2 <= 0 && c3 * c4 <= 0;
}

int main() {
  freopen("read", "r", stdin);
//  freopen("write", "w", stdout);
  
  int n;
  while (scanf("%d", &n) == 1 && n) {
    solver.init(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 4; j++) {
        p[i][j].read();
      }
      for (int j = 0; j < i; j++) {
        for (int a = 0; a < 2; a++) {
          for (int b = 0; b < 2; b++) {
            if (intersect(p[i][a], p[i][a^2], p[j][b], p[j][b^2])) {
              solver.add_clause(i, a^1, j, b^1);
            }
          }
        }
      }
    }
    printf("%s\n", solver.solve() ? "YES" : "NO");
  }
  return 0;
}
