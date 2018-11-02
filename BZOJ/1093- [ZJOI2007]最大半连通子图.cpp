#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;
const int M = 1e6+5;
int n, m, x, a, b;
vector<int> g[N], rg[N], sc[N];
int dfn[N], fn[N];
int dt, ft, group;
int ord[N], grp[N], wt[N];
bool in[N];
int f[N], cnt[N];
map<pair<int, int>, bool> linked;

void gather(int u) {
	grp[u] = group;
	wt[group]++;
	for (int i = 0; i < rg[u].size(); i++) {
		int v = rg[u][i];
		if (!grp[v]) {
			gather(v);
		} else 
		if (grp[v] < group && !linked[make_pair(grp[v], group)]) {
			sc[grp[v]].push_back(group);
			linked[make_pair(grp[v], group)] = true;
			in[group] = true;
		}
	}
}

bool cmp(int x, int y) {
	return fn[x] > fn[y];
}

void dfs(int u) {
	dfn[u] = ++dt;
	for (int i = 0; i < g[u].size(); i++) {
		if (!dfn[g[u][i]]) {
			dfs(g[u][i]);
		}
	}
	fn[u] = ++ft;
}

void compose() {
	for (int i = 1; i <= n; i++) {
		if (!dfn[i]) {
			dfs(i);
		}
	}
	for (int i = 1; i <= n; i++) {
		ord[i] = i;
	}
	sort(ord+1, ord+1+n, cmp);
	for (int i = 1; i <= n; i++) {
		if (!grp[ord[i]]) {
			group++;
			gather(ord[i]);
		}
	}
}

void dfs2(int u) {
	if (f[u] != -1) {
		return;
	}
	f[u] = wt[u];
	cnt[u] = 1;
	int opt = 0;
	for (int i = 0; i < sc[u].size(); i++) {
		int v = sc[u][i];
		dfs2(v);
		cnt[u] = f[v] > opt ? cnt[v] : cnt[u] + (f[v] == opt ? cnt[v] : 0) ;
		cnt[u] %= x;
		opt = max(opt, f[v]);
	}
	f[u] += opt;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> x;
	for (int i = 1; i <= m; i++) {
		cin >> a >> b;
		g[a].push_back(b);
		rg[b].push_back(a);
	}
	compose();
	int ans = 0, best = 0;
	memset(f, -1, sizeof(f));
	for (int i = 1; i <= group; i++) {
		if (!in[i]) {
			dfs2(i);
			ans = f[i] > best ? cnt[i] : ans + (f[i] == best ? cnt[i] : 0);
			ans %= x;
			best = max(best, f[i]);
		}
	}
	cout << best << endl << ans % x << endl;
	return 0;
}