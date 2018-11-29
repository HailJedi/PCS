/*
Created 2018-11-29
"[SHOI2014]概率充电器"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 500000 + 5;

struct Edge {
	Edge *next;
	int v;	
	double p;
	void *operator new (size_t, Edge *next, int v, double p) {
		static Edge pool[N*2], *pt = pool;
		Edge *ret = pt++;
		ret->next = next;
		ret->v = v;
		ret->p = p;
		return ret;
	}
} *head[N];

void add_edge(int u, int v, double p) {
	head[u] = new (head[u], v, p) Edge;
	head[v] = new (head[v], u, p) Edge;
}

double on[N];
double f[N], g[N];

void dfs1(int u, int fa) {
	f[u] = 1 - on[u];
	for (Edge *e = head[u]; e; e = e->next) {
		if (e->v != fa) {
			dfs1(e->v, u);
			f[u] *= (f[e->v] + (1 - f[e->v]) * (1 - e->p));
		}
	}
}

void dfs2(int u, int fa) {
	for (Edge *e = head[u]; e; e = e->next) {
		if (e->v != fa) {
			double P = g[u] * f[u] / (f[e->v] + (1 - f[e->v]) * (1 - e->p));
			g[e->v] = P + (1 - P) * (1 - e->p);
			dfs2(e->v, u);
		}
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int u, v;
		double p;
		scanf("%d %d %lf", &u, &v, &p);
		p /= 100;
		add_edge(u, v, p);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%lf", &on[i]);
		on[i] /= 100;
	}
	dfs1(1, 0);
	g[1] = 1;
	dfs2(1, 0);
	double ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += 1 - f[i] * g[i];
	}
	printf("%.6lf\n", ans);
	return 0;
}
