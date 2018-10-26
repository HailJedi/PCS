/*
Created 2018-10-26
"USACO 2011 December Contest, Gold Division
Problem 3. Grass Planting"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

/* BIT */

long long sum1[N], sum2[N];

int lowbit(int x) {
	return x & -x;
}

void add(int p, int v) {
	for (int i = p; i < N; i += lowbit(i)) {
		sum1[i] += v;
		sum2[i] += 1LL * v * p;
	}
}

void add(int l, int r, int v) {
	add(l, v);
	add(r+1, -v);
}

long long sum(int p) {
	long long ret = 0;
	for (int i = p; i; i -= lowbit(i)) {
		ret += (p+1) * sum1[i] - sum2[i];
	}
	return ret;
}

int sum(int l, int r) {
	return sum(r) - sum(l-1);
}

/* HL Decomposition */

vector<int> g[N];
int fa[21][N], sz[N], dep[N];
int pref[N], top[N];
int ct, id[N];

void dfs1(int u, int f) {
	fa[0][u] = f;
	sz[u] = 1;
	dep[u] = dep[f] + 1;
	for (int v: g[u]) {
		if (v != f) {
			dfs1(v, u);
			sz[u] += sz[v];
			if (sz[v] > sz[pref[u]]) {
				pref[u] = v;
			}
		}
	}
}

void dfs2(int u, int tp) {
	top[u] = tp;
	id[u] = ++ct;
	if (pref[u] != 0) {
		dfs2(pref[u], tp);
	}
	for (int v: g[u]) {
		if (id[v] == 0) {
			dfs2(v, v);
		}
	}
}

int query_sum(int x, int y) {
	int ret = 0;
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) {
			swap(x, y);
		}
		ret += sum(id[top[x]], id[x]);
		x = fa[0][top[x]];
	}
	if (id[x] > id[y]) {
		swap(x, y);
	}
	ret += sum(id[x], id[y]);
	return ret;
}

void change_sum(int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) {
			swap(x, y);
		}
		add(id[top[x]], id[x], 1);
		x = fa[0][top[x]];
	}
	if (id[x] > id[y]) {
		swap(x, y);
	}
	add(id[x], id[y], 1);
}

int find_lca(int x, int y) {
	if (dep[x] < dep[y]) {
		swap(x, y);
	}
	for (int i = 20; i >= 0; i--) {
		if (dep[fa[i][x]] >= dep[y]) {
			x = fa[i][x];
		}
	}
	if (x == y) {
		return x;
	}
	for (int i = 20; i >= 0; i--) {
		if (fa[i][x] != fa[i][y]) {
			x = fa[i][x];
			y = fa[i][y];
		}
	}
	return fa[0][x];
}

int aproach(int x, int tar) {
	for (int i = 20; i >= 0; i--) {
		if (dep[fa[i][x]] > dep[tar]) {
			x = fa[i][x];
		}
	}
	return x;
}

int main() {
	freopen("grassplant.in", "r", stdin);
	freopen("grassplant.out", "w", stdout);
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	for (int i = 1; i <= n; i++) {
	}
	for (int i = 1; i <= 20; i++) {
		for (int u = 1; u <= n; u++) {
			fa[i][u] = fa[i-1][fa[i-1][u]];
		}
	}
	while (m--) {
		char cmd[10];
		int x, y;
		scanf("%s %d %d", cmd, &x, &y);
		if (dep[x] < dep[y]) {
			swap(x, y);
		}
		int lca = find_lca(x, y);
		if (lca == y) {
			int xx = aproach(x, lca);
			if (cmd[0] == 'Q') {
				printf("%d\n", query_sum(x, xx));
			} else {
				change_sum(x, xx);
			}
		} else {
			int xx = aproach(x, lca);
			int yy = aproach(y, lca);
			if (cmd[0] == 'Q') {
				printf("%d\n", query_sum(x, xx) + query_sum(y, yy));
			} else {
				change_sum(x, xx);
				change_sum(y, yy);
			}
		}
	}
	return 0;
}
