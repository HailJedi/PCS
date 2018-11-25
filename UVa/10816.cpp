#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;
const int M = N*N;
const double INF = 1e30;

struct Edge {
	int u, v;
	double r, d;
	void *operator new(size_t, int u, int v, double r, double d) {
		static Edge pool[M], *p = pool;
		if (p == pool + M) {
			p = pool;
		}
		Edge *ret = p++;
		ret->u = u;
		ret->v = v;
		ret->r = r;
		ret->d = d;
		return ret;
	}
} *edge[M];

struct cmp {
	bool operator () (const Edge *e1, const Edge *e2) const {
		return e1->r < e2->r;
	}
};

int mid[N][N];
double dis[N][N];

void print(int u, int v) {
	if (mid[u][v] == -1) {
		return;
	}
	print(u, mid[u][v]);
	printf(" %d", mid[u][v]);
	print(mid[u][v], v);
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

bool update(double &x, double y) {
	if (x > y) {
		x = y;
		return true;
	}
	return false;
}

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	int n, m, s, t;
	while (scanf("%d %d", &n, &m) == 2) {
		scanf("%d %d", &s, &t);
		for (int i = 1; i <= m; i++) {
			int u, v;
			double r, d;
			scanf("%d %d %lf %lf", &u, &v, &r, &d);
			edge[i] = new (u, v, r, d) Edge;
		}
		sort(edge+1, edge+1+m, cmp());
		for (int i = 1; i <= n; i++) {
			fa[i] = i;
			rk[i] = 1;
		}
		double lim = 0;
		for (int i = 1; i <= m && find(s) != find(t); i++) {
			int u = find(edge[i]->u), v = find(edge[i]->v);
			if (u != v) {
				unite(u, v);
				lim = edge[i]->r;
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				dis[i][j] = INF;
			}
			dis[i][i] = 0;
		}
		for (int i = 1; i <= m; i++) {
			if (edge[i]->r <= lim) {
				update(dis[edge[i]->u][edge[i]->v], edge[i]->d);
				update(dis[edge[i]->v][edge[i]->u], edge[i]->d);
			}
		}
		memset(mid, -1, sizeof mid);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				for (int k = 1; k <= n; k++) {
					if (update(dis[j][k], dis[j][i] + dis[i][k])) {
						mid[j][k] = i;
					}
				}
			}
		}
		printf("%d", s);
		print(s, t);
		printf(" %d", t);
		printf("\n");
		printf("%.1lf %.1lf\n", dis[s][t], lim);
	}
	return 0;
}
