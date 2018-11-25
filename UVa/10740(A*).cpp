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

int d[N][N];
int x, y, k;

struct State {
	int u, ds;
	State(int u, int ds) : u(u), ds(ds) {}
	bool operator < (const State &s) const {
		return ds + d[u][y] > s.ds + d[s.u][y];
	}
};

void update(int &x, int y) {
	if (x > y) {
		x = y;
	}
}

int AStar() {
	priority_queue<State> q;
	q.push(State(x, 0));
	int cnt = 0;
	while (!q.empty()) {
		State s = q.top();
		q.pop();
		cnt += (s.u == y);
		if (cnt == k) {
			return s.ds;
		}
		for (Edge *e = head[s.u]; e; e = e->next) {
			q.push(State(e->v, s.ds + e->w));
		}
	}
	return INF;
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
		int ans = AStar();
		if (ans != INF) {
			printf("%d\n", ans);
		} else {
			printf("%s\n", "-1");
		}
	}
	return 0;
}