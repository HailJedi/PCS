#include <bits/stdc++.h>

using namespace std;

#define N 300010
#define INF 1e9
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define sz(x) x.size()

vector<int> g[N], ans, rec;
set<pair<int, int>> edge;
int n, m, u, v;
int dis[N], fa[N], in[N];
int cls[N], vis[N];

void dfs(int u) {
	rec.pb(u); vis[u] = 1;
	for (int v: g[u]) if (!vis[v]) dfs(v);
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &u, &v);
		g[u].pb(v); g[v].pb(u);
		edge.insert(mp(u, v));
		edge.insert(mp(v, u));
	}

	for (int i = 2; i <= n; i++) dis[i] = INF;
	queue<int> que; que.push(1);
	while (!que.empty()) {
		int u = que.front(); que.pop(); in[u] = 0;
		for (int v: g[u]) if (dis[v] > dis[u] + 1) {
			dis[v] = dis[u] + 1; fa[v] = u;
			if (!in[v]) { in[v] = 1; que.push(v); }
		}
	}
	if (dis[n] != INF) {
		for (int u = n; u; u = fa[u]) ans.pb(u);
		reverse(all(ans));
	}

	if (ans.empty() || sz(ans) > 4) {
		for (int u: g[1]) cls[u] = 1; cls[1] = 1;
		bool ok = false;
		for (int u: g[1]) {
			for (int v: g[u]) if (!cls[v]) 
				{ ans = { 1, u, v, 1, n }; ok = true; break; }
			if (ok) break;
		}
	}

	if (ans.empty() || sz(ans) > 5) {
		vis[1] = 1; bool ok = false;
		for (int u: g[1]) {
			if (vis[u]) continue;
			rec.clear(); dfs(u);
			if (sz(g[u]) != sz(rec)) { // not a clique
				int cur = 1; while (cur < sz(rec) && edge.count({u, rec[cur]})) cur++;
				for (int i = 1; i < cur; i++) if (edge.count({rec[i], rec[cur]})) {
					ans = { 1, u, rec[i], rec[cur], u, n }; ok = true;
				}
			} else {
				for (int i = 0; i < sz(g[u]); i++) {
				for (int j = i+1; j < sz(g[u]); j++)
					if (g[u][i] != 1 && g[u][j] != 1 && !edge.count({g[u][i], g[u][j]})) 
						{ ans = { 1, g[u][i], u, g[u][j], g[u][i], n }; ok = true; break; }
				} if (ok) break;
			} if (ok) break;
		}
	}

	if (ans.empty()) puts("-1");
	else {
		printf("%d\n", (int)sz(ans)-1);
		for (int u: ans) printf("%d ", u); 
		puts("");
	}

	return 0;
}