#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;
const int INF = 0x3f3f3f3f;

int d[N][N], d2[N][N];

struct Edge {
  Edge *next;
  int u, v, w;
  void *operator new(size_t, Edge *next, int u, int v, int w) {
    static Edge pool[N*N*2], *p = pool;
    if (p == pool + N*N*2) {
      p = pool;
    }
    Edge *ret = p++;
    ret->next = next;
    ret->u = u;
    ret->v = v;
    ret->w = w;
    return ret;
  }
} *head[N];

void add_edge(int u, int v, int w) {
  head[u] = new (head[u], u, v, w) Edge;
}

void update(int &x, int y) {
	if (x > y) {
		x = y;
	}
}

void dfs(int s, int u, int ds) {
  if (d2[s][u] <= ds) {
    return;
  }
  if (ds > d[s][u]) {
		update(d2[s][u], ds);
  }
  for (Edge *e = head[u]; e; e = e->next) {
    dfs(s, e->v, ds + e->w);
  }
}

void dfs2(int s, int t, int u, int ds) {
	if (ds + d[u][t] >= d2[s][t]) {
		return;
	}
	if (ds + d[u][t] > d[s][t]) {
		update(d2[s][t], ds + d[u][t]);
	}
	for (Edge *e = head[u]; e; e = e->next) {
		dfs2(s, t, e->v, ds + e->w);
	}
}

int main() {
//  freopen("read", "r", stdin);
//  freopen("write", "w", stdout);

  int n, m, kase = 0;
  while (scanf("%d %d", &n, &m) == 2) {
    memset(head, 0x0, sizeof head);
    memset(d, INF, sizeof d);
    memset(d2, INF, sizeof d2);
		for (int i = 0; i < n; i++) {
			d[i][i] = 0;
		}
    for (int i = 1; i <= m; i++) {
      int u, v, w;
      scanf("%d %d %d", &u, &v, &w);
			update(d[u][v], w);
			update(d[v][u], w);
      add_edge(u, v, w);
      add_edge(v, u, w);
    }
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
					update(d[i][j], d[i][k] + d[k][j]);
        }
      }
    }
		/*
    for (int i = 0; i < n; i++) {
      dfs(i, i, 0);
    }
		*/
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++) {
				if (d[i][j] != INF) {
					dfs2(i, j, i, 0);
					d2[j][i] = d2[i][j];
				}
			}
		}
    printf("Set #%d\n", ++kase);
    int q;
    scanf("%d", &q);
    while (q--) {
      int u, v;
      scanf("%d %d", &u, &v);
      if (d2[u][v] != INF) {
        printf("%d\n", d2[u][v]);
      } else {
        printf("%c\n", '?');
      }
    }
  }
  return 0;
}
