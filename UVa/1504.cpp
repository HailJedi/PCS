#include <bits/stdc++.h>

using namespace std;

const int N = 3000 + 5;
const int M = N * N;
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
} *head[N], *edge[M];

struct cmp {
	bool operator () (const Edge *e1, const Edge *e2) const {
		return e1->w < e2->w;
	}
};

void add_edge(int u, int v, int w) {
	head[u] = new (head[u], u, v, w) Edge;
}

bool in[N][N];
int dis[N][N];
int d2r[N][N];
int d[N][N];

void update(int &x, int y) {
	if (x > y) {
		x = y;
	}
}

void dfs(int root, int u, int fa) {
	for (Edge *e = head[u]; e; e = e->next) {
		if (e->v != fa) {
			dfs(root, e->v, u);
			update(d2r[u][root], d2r[e->v][root]);
			update(dis[u][e->v], d2r[e->v][root]);
			update(dis[e->v][u], d2r[e->v][root]);
		}
	}
	if (fa != root) {
		update(d2r[u][root], d[u][root]);
	}
}			

int fa[N], rk[N];

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void unite(int x, int y) {
	if (rk[x] < rk[y]) {
		fa[x] = y;
		rk[y] += rk[x];
	} else {
		fa[y] = x;
		rk[x] += rk[y];
	}
}

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	int n, m;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		memset(d, INF, sizeof d);
		memset(d2r, INF, sizeof d2r);
		memset(dis, INF, sizeof dis);
		memset(head, 0x0, sizeof head);
		memset(in, false, sizeof in);
		for (int i = 0; i < m; i++) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			edge[i] = new (0x0, u, v, w) Edge;
			update(d[u][v], w);
			update(d[v][u], w);
		}
		sort(edge, edge+m, cmp());
		int cnt = 0, sum = 0;
		for (int i = 0; i < n; i++) {
			fa[i] = i;
			rk[i] = 1;
		}
		for (int i = 0; i < m && cnt < n-1; i++) {
			int u = edge[i]->u, v = edge[i]->v;
			int fu = find(u), fv = find(v);
			if (fu != fv) {
				unite(fu, fv);
				cnt++;
				sum += edge[i]->w;
				in[u][v] = in[v][u] = true;
				add_edge(u, v, edge[i]->w);
				add_edge(v, u, edge[i]->w);
			}
		}
		for (int i = 0; i < n; i++) {
			dfs(i, i, -1);
		}
		int Q;
		scanf("%d", &Q);
		double ans = 0;
		for (int i = 0; i < Q; i++) {
			int u, v, c;
			scanf("%d %d %d", &u, &v, &c);
			if (in[u][v]) {
				ans += min(c, dis[u][v]) - d[u][v];
			}
		}
		printf("%.4lf\n", ans / Q + sum);
	}
	return 0;
}
