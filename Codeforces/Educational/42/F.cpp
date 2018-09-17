#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

#define pb push_back
#define mp make_pair
#define ft first
#define sc second

vector<int> son[N], root, pe, ans;
vector<pair<int, int>> e[N];
pair<int, int> E[N], par[N];
int cnt[N], cnt2[N], dfn[N];
int n, m, u, v, dt;

void dfs(int u) {
	dfn[u] = ++dt;
	for (auto p: e[u]) {
		int v = p.ft, id = p.sc;
		if (!dfn[v]) {
			dfs(v);
			son[u].pb(v);
			par[v] = mp(u, id);
		} else 
		if (dfn[u] < dfn[v]) {
			cnt[u]--; cnt[v]++;
			pe.pb(id);
		}
	}
}

void dfs2(int u) {
	for (auto v: son[u]) {
		dfs2(v);
		cnt[u] += cnt[v];
	}
	cnt2[u] = cnt[u]>=2;
}

void dfs3(int u) {
	for (auto v: son[u]) {
		cnt2[v] += cnt2[u];
		dfs3(v);
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &u, &v);
		E[i] = mp(u, v);
		e[u].pb(mp(v, i));
		e[v].pb(mp(u, i));
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) {
			dfs(i); 
			root.pb(i);
		}
	for (int u: root) dfs2(u);
	for (int u: root) dfs3(u);

	for (int p: pe) {
		int u = E[p].ft, v = E[p].sc;
		if (dfn[v] < dfn[u]) swap(u, v);
		if (cnt2[u] == cnt2[v]) {
			ans.pb(p);
			while (v != u) {
				ans.pb(par[v].sc);
				v = par[v].ft;
			}
		}
	}
	sort(ans.begin(), ans.end());
	printf("%d\n", (int)ans.size());
	for (int p : ans) printf("%d ", p);
	return 0;
}
