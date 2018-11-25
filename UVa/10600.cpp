#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;
const int M = N * N;

struct Edge {
	Edge *next;
	int u, v, w;
	bool in;
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
		ret->in = false;
		return ret;
	}
} *edge[M], *head[N];

struct cmp {
	bool operator() (const Edge *e1, const Edge *e2) const {
		return e1->w < e2->w;
	}
};

void add_edge(int u, int v, int w) {
	head[u] = new(head[u], u, v, w) Edge;
}

int dis[N][N];

void dfs(int root, int u, int f, int d) {
	dis[root][u] = d;
	for (Edge *e = head[u]; e; e = e->next) {
		if (e->v != f) {
			dfs(root, e->v, u, max(d, e->w));
		}
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
	
	int T;
	cin >> T;
	while (T--) {
		int n, m;
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= m; i++) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			edge[i] = new (0x0, u, v, w) Edge;
		}
		sort(edge+1, edge+1+m, cmp());
		for (int i = 1; i <= n; i++) {
			fa[i] = i;
			rk[i] = 1;
		}
		int cnt = 0, ans1 = 0;
		memset(head, 0x0, sizeof head);
		for (int i = 1; i <= m; i++) {
			int u = edge[i]->u, v = edge[i]->v, w = edge[i]->w;
			int fu = find(u), fv = find(v);
			if (fu != fv) {
				unite(fu, fv);
				cnt++;
				edge[i]->in = true;
				add_edge(u, v, w);
				add_edge(v, u, w);
				ans1 += w;
				if (cnt == n-1) {
					break;
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			dfs(i, i, -1, 0);
		}
		int ans2 = 1e9;
		for (int i = 1; i <= m; i++) {
			if (!edge[i]->in) {
				ans2 = min(ans2, ans1 - dis[edge[i]->u][edge[i]->v] + edge[i]->w);
			}
		}
		printf("%d %d\n", ans1, ans2);
	}
	return 0;
}
