#include <bits/stdc++.h>

using namespace std;

#define fs first
#define sc second
#define pb push_back
#define all(x) x.begin(), x.end()

typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 500010;

int n, m, dt;
vector< vector<pii> > g;
vector < vi > cycles;
int low[N], idx[N], cid[N], fa[N], maxl[N], L[N], Z[N];
bool is_bridge[N<<1], vis[N];

void dfs1(int u, int p) {
	low[u] = idx[u] = ++dt;
	for (auto e: g[u]) {
		int v = e.fs;
		if (!idx[v]) {
			dfs1(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] > idx[u])
				is_bridge[e.sc] = true;
		} else
		if (v != p) low[u] = min(low[u], idx[v]);
	}
}

void dfs2(int u) {
	vis[u] = true;
	cycles.back().pb(u);
	cid[u] = cycles.size()-1;
	for (auto e: g[u])  
		if (!is_bridge[e.sc] && !vis[e.fs]) 
			dfs2(e.fs);
}

void bfs(int u) {
	queue<int> q;
	vi topo;
	q.push(u);
	memset(vis, false, sizeof(bool)*(n+1));
	vis[u] = true;
	fa[u] = -1;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		topo.pb(u);
		for (auto e: g[u]) {
			int v = e.fs;
			if (!vis[v])
				vis[v] = true, fa[v] = u, q.push(v);
		}
	}
	reverse(all(topo));
	for (auto u: topo) for (auto e: g[u]) {
		int v = e.fs;
		if (fa[v] == u) {
			maxl[u] = max(maxl[u], maxl[v]+1);
			if (is_bridge[e.sc]) 
				L[u] = max(L[u], 1 + maxl[v]);
		}
	}
}

void dfs3(int u, int p, int c) {
	L[u] = max(L[u], c);
	vi &cycle = cycles[cid[u]];
	int k = cycle.size();
	for (int it = 0; it < 2; it++) {
		priority_queue<pii> q;
		for (int i = 0; i < 2 * k; i++) {
			int d = 2 * k - i;
			while (!q.empty() && q.top().sc - d > k / 2) q.pop();
			if (!q.empty()) Z[cycle[i%k]] = max(Z[cycle[i%k]], q.top().fs - d);
			q.push({ L[cycle[i%k]] + d, d });
		}
		reverse(all(cycle));
	}
	for (auto u: cycle) {
		int st1 = 0, nd2 = 0;
		for (auto e: g[u]) {
			if (e.fs != p && is_bridge[e.sc]) {
				int v = e.fs;
				nd2 = max(nd2, 1 + maxl[v]);
				if (nd2 > st1) swap(st1, nd2);
			}
		}
		for (auto e: g[u]) {
			if (e.fs != p && is_bridge[e.sc]) {
				int v = e.fs;
				int pc = max(c, Z[u]);
				if (st1 == 1 + maxl[v]) pc = max(pc, nd2);
				else pc = max(pc, st1);
				dfs3(v, u, pc+1);
			}
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	g.resize(n+1);
	int u, v;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &u, &v);
		g[u].pb({v, i}); g[v].pb({u, i});
	}
	dfs1(1, 0);
	for (int i = 1; i <= n; i++) 
		if (!vis[i]) { 
			cycles.pb(vector<int>()); 
			dfs2(i); 
		}
	bfs(1);
	dfs3(1, 0, 0);
	for (int i = 1; i <= n; i++)
		printf("%d ", max(L[i], Z[i]));
	puts("");
	return 0;
}