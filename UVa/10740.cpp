#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;
const int M = 1000 + 5;
const int INF = 0x3f3f3f3f;

struct Edge {
	Edge *next;
	int u, v, w;
	void *operator new(size_t, Edge *next, int u, int v, int w) {
		static Edge pool[M], *p = pool;
		if (p == pool + M) {
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

priority_queue<int> q;
int x, y, k, way;
int d[N][N];

bool run(int u, int ds, int lim) {
	if (u == y) {
		way += (ds <= lim);
	}
	if (way >= k) {
		return true;
	}
	for (Edge *e = head[u]; e; e = e->next) {
		if (ds + e->w + d[e->v][y] <= lim && run(e->v, ds + e->w, lim)) {
			return true;
		}		
	}
	return way >= k;
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int n, m;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		scanf("%d %d %d", &x, &y, &k);
		memset(head, 0x0, sizeof head);
		memset(d, INF, sizeof d);
		for (int i = 1; i <= m; i++) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			add_edge(u, v, w);
			update(d[u][v], w);
		}
		for (int i = 1; i <= n; i++) {
			d[i][i] = 0;
		}
		for (int k = 1; k <= n; k++) {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					update(d[i][j], d[i][k] + d[k][j]);
				}
			}
		}
		int l = 0, r = INF;
		while (r - l > 1) {
			int mid = (l + r) / 2;
			way = 0;
			if (run(x, 0, mid)) {
				r = mid;
			} else {
				l = mid;
			}
		}
		if (r == INF) {
			printf("%s\n", "-1");
		} else {
			printf("%d\n", r);
		}
	}
	return 0;
}