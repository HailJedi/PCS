#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;
const int M = N * N;
const int INF = 0x3f3f3f3f;

struct Point {
	int x, y, z;
	void *operator new(size_t, int x, int y, int z) {
		static Point pool[N], *p = pool;
		if (p == pool + N) {
			p = pool;
		}
		Point *ret = p++;
		p->x = x;
		p->y = y;
		p->z = z;
		return p;
	}
} *pt[N];

int dist(int i, int j) {
	return ceil(sqrt(pow(pt[i]->x-pt[j]->x, 2) + pow(pt[i]->y-pt[j]->y, 2) + pow(pt[i]->z-pt[j]->z, 2)));
}

struct Edge {
	Edge *next;
	int u, v, w, d;
	void *operator new(size_t, Edge *next, int u, int v, int w, int d) {
		static Edge pool[M], *p = pool;
		if (p == pool + M) {
			p = pool;
		}
		Edge *ret = p++;
		ret->next = next;
		ret->u = u;
		ret->v = v;
		ret->w = w;
		ret->d = d;
		return ret;
	}
} *head[N];

void add_edge(int u, int v, int w, int d) {
	head[u] = new (head[u], u, v, w, d) Edge;
}

int dis[N];
bool inq[N];
queue<int> q;

int bellmanford(int s, int t) {
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = false;
		for (Edge *e = head[u]; e; e = e->next) {
			int w = e->w + max(0, e->d - dis[u]);
			if (dis[e->v] > dis[u] + w) {
				dis[e->v] = dis[u] + w;
				if (!inq[e->v]) {
					q.push(e->v);
					inq[e->v] = true;
				}
			}
		}
	}
	return dis[t];
}

bool vis[N];
Edge* stk[M];
int tp;

void dfs(int u) {
	vis[u] = true;
	for (Edge *e = head[u]; e; e = e->next) {
		stk[++tp] = e;
		if (!vis[e->v]) {
			int w = e->w + max(0, e->d - dis[u]);
			if (dis[e->v] > dis[u] + w) {
				dis[e->v] = dis[u] + w;
				dfs(e->v);
			}
		} else {
			int sum = 0;
			Edge *piv = e;
			for (int i = tp; i; i--) {
				Edge *x = stk[i];
				sum += x->w;
				if (x->d > piv->d) {
					piv = x;
				}
				if (x->u == e->v) {
					break;
				}
			}
			if (sum < 0 && piv->d != -INF) {
				dis[piv->u] = piv->d;
				if (!inq[piv->u]) {
					q.push(piv->u);
					inq[piv->u] = true;
				}
			}
		}
		--tp;
	}
	vis[u] = false;
}

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	int T;
	scanf("%d", &T);
	while (T--) {
		int n = 0;
		int x0, x1, y0, y1, z0, z1;
		scanf("%d %d %d %d %d %d", &x0, &y0, &z0, &x1, &y1, &z1);
		pt[n++] = new (x0, y0, z0) Point;
		pt[n++] = new (x1, y1, z1) Point;
		int s = 0, t = 1, m;
		scanf("%d", &m);
		memset(head, 0x0, sizeof head);
		for (int i = 1; i <= m; i++) {
			int w, d;
			scanf("%d %d %d %d %d %d %d %d", &x0, &y0, &z0, &x1, &y1, &z1, &d, &w);
			pt[n++] = new (x0, y0, z0) Point;
			pt[n++] = new (x1, y1, z1) Point;
			add_edge(n-2, n-1, w, d);
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i != j) {
					add_edge(i, j, dist(i, j), -INF);
				}
			}
		}
		memset(dis, INF, sizeof dis);
		dis[s] = 0;
		q.push(s);
		inq[s] = true;
		dfs(s);
		printf("%d\n", bellmanford(s, t));
	}
	return 0;
}
