#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
const int M = N * N;

struct Edge {
	Edge *next;
	int u, v;
	double w;
	void *operator new(size_t, Edge *next, int u, int v, double w) {
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
} *edge[M], *head[N];

struct cmp {
	bool operator () (const Edge *e1, const Edge *e2) {
		return e1->w < e2->w;
	}
};

void add_edge(int u, int v, double w) {
	head[u] = new (head[u], u, v, w) Edge;
}

double x[N], y[N], p[N];

double dist(int i, int j) {
	return sqrt(pow(x[i]-x[j], 2) + pow(y[i]-y[j], 2));
}

int an[N], rk[N];

int find(int x) {
	return x == an[x] ? x : an[x] = find(an[x]);
}

void unite(int x, int y) {
	if (rk[x] < rk[y]) {
		an[x] = y;
		rk[y] += rk[x];
	} else {
		an[y] = x;
		rk[x] += rk[y];
	}
}

double dis[N][N];

void dfs(int root, int u, int f, double d) {
	dis[root][u] = d;
	for (Edge *e = head[u]; e; e = e->next) {
		if (e->v != f) {
			dfs(root, e->v, u, max(d, e->w));
		}
	}
}

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%lf %lf %lf", &x[i], &y[i], &p[i]);
		}
		int m = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = i+1; j <= n; j++) {
				edge[m++] = new (0x0, i, j, dist(i, j)) Edge;
			}
		}
		sort(edge, edge+m, cmp());
		for (int i = 1; i <= n; i++) {
			an[i] = i;
			rk[i] = 1;
		}
		double sum = 0;
		int cnt = 0;
		memset(head, 0x0, sizeof head);
		for (int i = 0; i < m && cnt < n-1; i++) {
			int u = find(edge[i]->u), v = find(edge[i]->v);
			if (u != v) {
				add_edge(edge[i]->u, edge[i]->v, edge[i]->w);
				add_edge(edge[i]->v, edge[i]->u, edge[i]->w);
				unite(u, v);
				cnt++;
				sum += edge[i]->w;
			}
		}
		double ans = 0;
		for (int i = 1; i <= n; i++) {
			dfs(i, i, -1, 0);
			for (int j = i+1; j <= n; j++) {
				ans = max(ans, (p[i]+p[j]) / (sum - dis[i][j]));
			}
		}
		printf("%.2lf\n", ans);
	}
	return 0;
}
