#include <bits/stdc++.h>

using namespace std;

const int N = 500 + 5;
const int M = N * N;

struct Edge {
	int u, v;
	double w;
	bool in;
	void *operator new(size_t, int u, int v, double w) {
		static Edge pool[M], *p = pool;
		if (p == pool + M) {
			p = pool;
		}
		Edge *ret = p++;
		ret->u = u;
		ret->v = v;
		ret->w = w;
		ret->in = false;
		return ret;
	}
} *edge[M];

struct cmp {
	bool operator () (const Edge *e1, const Edge *e2) const {
		return e1->w < e2->w;
	}
};

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

double x[N], y[N];

double dist(int i, int j) {
	return sqrt(pow(x[i]-x[j], 2) + pow(y[i]-y[j], 2));
}

bool ins[N];

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	int T;
	scanf("%d", &T);
	while (T--) {
		int s, n;
		scanf("%d %d", &s, &n);
		for (int i = 1; i <= n; i++) {
			scanf("%lf %lf", &x[i], &y[i]);
		}
		int m = 0;
		for (int i = 1; i < n; i++) {
			for (int j = i+1; j <= n; j++) {
				edge[m++] = new (i, j, dist(i, j)) Edge;
			}
		}
		sort(edge, edge+m, cmp());
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			fa[i] = i;
			rk[i] = 1;
		}
		double ans = 0;
		for (int i = 0; i < m && cnt < n-1; i++) {
			int u = find(edge[i]->u), v = find(edge[i]->v);
			if (u != v) {
				unite(u, v);
				cnt++;
				if (cnt == n-s) {
					ans = edge[i]->w;
					break;
				}
			}
		}
		printf("%.2lf\n", ans);
	}
	return 0;
}
