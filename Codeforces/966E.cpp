#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
const int S = 332;
const int INF = 1e9;

int n, m, G, ft;
int fa[N], t[N], s[N];
vector<int> son[N];
int dfn[N], grp[N], l[S], r[S];
int top[N], dpth[N], prf[N], sz[N], tag[S];
bool off[N];

void dfs1(int u, int f) {
	sz[u] = 1; dpth[u] = dpth[f] + 1;
	for (int v: son[u]) {
		dfs1(v, u); sz[u] += sz[v];
		if (sz[v] > sz[prf[u]]) prf[u] = v;
	}
}

void dfs2(int u, int t) {
	top[u] = t; dfn[u] = ++ft;
	if (prf[u]) dfs2(prf[u], t);
	for (int v: son[u])
		if (v != prf[u]) dfs2(v, v);
}

void update(int g) {
	for (int i = l[g]; i <= r[g]; i++) {
		t[i] += tag[g];
		if (off[i]) s[i] = INF;
		else s[i] = t[i];
	}
	sort(s+l[g], s+r[g]+1);
	tag[g] = 0;
}

void add(int u, int v, int x) {
	if (grp[u] == grp[v]) {
		for (int i = u; i <= v; i++) t[i] += x;
		update(grp[u]);
	} else {
		for (int i = u; i <= r[grp[u]]; i++) t[i] += x;
		for (int i = l[grp[v]]; i <= v; i++) t[i] += x;
		update(grp[u]); update(grp[v]);
		for (int i = grp[u]+1; i <= grp[v]-1; i++) tag[i] += x;
	}
}

void modify(int u, int v, int x) {
	while (top[v] != top[u]) {
		if (dpth[top[u]] < dpth[top[v]]) swap(u, v);
		add(dfn[top[u]], dfn[u], x);
		u = fa[top[u]];
	}
	if (dpth[u] < dpth[v]) swap(u, v);
	add(dfn[v], dfn[u], x);
}

int query() {
	int ret = 0;
	for (int i = 1; i <= G; i++)
		ret += lower_bound(s+l[i], s+r[i]+1, -tag[i])-s-l[i];
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 2; i <= n; i++) {
		cin >> fa[i];
		son[fa[i]].push_back(i);
	}
	dfs1(1, 0); dfs2(1, 1);
	for (int i = 1; i <= n; i++) cin >> t[dfn[i]];
	for (int i = 1; i <= n; i++) {
		if (i % S == 1) grp[i] = grp[i-1]+1, l[grp[i]] = i;
		else grp[i] = grp[i-1];
		r[grp[i]] = i;
	}
	G = grp[n];
	for (int i = 1; i <= G; i++) update(i);
	int psn;
	while (m--) {
		cin >> psn;
		if (psn > 0) {
			off[dfn[psn]] = true;
			modify(1, psn, -1);
			update(grp[dfn[psn]]);
		} else {
			psn = -psn;
			off[dfn[psn]] = false;
			modify(1, psn, 1);
			update(grp[dfn[psn]]);
		}
		cout << query() << ' ';
	}
	return 0;
}