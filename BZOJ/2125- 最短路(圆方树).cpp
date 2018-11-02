#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;
vector<int> g[N], rs_g[N];
int uv[N], rs_uv[N];
int n, m, q, u, v;
int dfn[N], low[N], fa[N], d;
long long sum[N], sz[N], w[N*2], rs_w[N*4];
int sq;

void rs_addedge(int u, int v, int w) {
	// cout << "rs-edge " << u << "-" << v << " weighs " << w << endl;
	rs_g[u].push_back(++m);
	rs_g[v].push_back(m);
	rs_w[m] = w;
	rs_uv[m] = u + v;
}

void dfs(int u) {
	dfn[u] = low[u] = ++d;
	for (int i = 0; i < g[u].size(); i++) {
		int e = g[u][i];
		int v = uv[e] - u;
		if (v != fa[u]) {
			if (!dfn[v]) {
				sum[v] = sum[u] + w[e];
				fa[v] = u;
				dfs(v);
				low[u] = min(low[u], low[v]);
			} else 
			if (dfn[v] < dfn[u]) {
				low[u] = min(low[u], dfn[v]);
			} else
			if (low[v] == dfn[u]) {
				// cout << "linking " << u << " and " << sq+1 << endl;
				rs_addedge(u, ++sq, 0);
				sz[sq] = sum[v] - sum[u] + w[e];
				for (int x = v; x != u; x = fa[x]) {
					// cout << "linking " << sq << " and " << x << endl;
					rs_addedge(sq, x, min(sum[x] - sum[u], sz[sq] - (sum[x] - sum[u])));
				}
			} 
			if (dfn[u] < low[v]) {
				// cout << "linking " << u << " and " << v << endl;
				rs_addedge(u, v, w[e]);
			}
		}
	}
}

const long long INF = 1e18;
const int LG = 22;
int bfa[N][LG], dp[N];
typedef pair<long long, int> pdi;
long long dist[N];

void bfs() {
	priority_queue<pdi> q;
	q.push(make_pair(0, 1));
	for (int i = 2; i <= sq; i++) {
		dist[i] = INF;
	}
	while (!q.empty()) {
		pdi p = q.top(); q.pop();
		int u = p.second;
		for (int i = 0; i < rs_g[u].size(); i++) {
			int rs_e = rs_g[u][i];
			int v = rs_uv[rs_e] - u;
			if (dist[v] > dist[u] + rs_w[rs_e]) {
				dist[v] = dist[u] + rs_w[rs_e];
				bfa[v][0] = u;
				dp[v] = dp[u] + 1;
				q.push(make_pair(-dist[v], v));
			}
		}
	}
}

void dfs2(int u, int f) {
	cout << u << ' ';
	for (int i = 0; i < rs_g[u].size(); i++) {
		int rs_e = rs_g[u][i];
		int v = rs_uv[rs_e] - u;
		if (v != f) {
			dfs2(v, u);
		}
	}
}

int LCA(int u, int v) {
	if (dp[u] < dp[v]) {
		swap(u, v);
	}
	for (int i = LG - 1; i >= 0; i--) {
		if (dp[bfa[u][i]] >= dp[v]) {
			u = bfa[u][i];
		}
	}
	if (u == v) {
		return u;
	}
	for (int i = LG - 1; i >= 0; i--) {
		if (bfa[u][i] != bfa[v][i]) {
			u = bfa[u][i];
			v = bfa[v][i];
		}
	}
	return bfa[u][0];
}

int aproach(int u, int tar) {
	if (bfa[u][0] == tar) {
		return u;
	}
	for (int i = LG - 1; i >= 0; i--) {
		if (dp[bfa[u][i]] >= dp[tar] && bfa[u][i] != tar) {
			u = bfa[u][i];
		}
 	}
 	// assert(bfa[u][0] == tar);
 	return u;
}

int main() {
	scanf("%d %d %d", &n, &m, &q);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %lld", &u, &v, &w[i]);
		g[u].push_back(i);
		g[v].push_back(i);
		uv[i] = u + v;
	}
	m = 0;
	sq = n;
	dfs(1);
	// dfs2(1, 0);
	// cout << endl;
	bfs();
	// for (int i = 1; i <= n; i++) {
	// 	cout << dist[i] << ' ';
	// }
	// cout << endl;
	for (int i = 1; i < LG; i++) {
		for (int j = 1; j <= sq; j++) {
			bfa[j][i] = bfa[bfa[j][i-1]][i-1];
		}
	}
	while (q--) {
		scanf("%d %d", &u, &v);
		// cout << u << "-" << v << ": ";
		int lca = LCA(u, v);
		if (lca <= n) {
			printf("%lld\n", dist[u] + dist[v] - 2 * dist[lca]);
		} else {
			int uu = aproach(u, lca), vv = aproach(v, lca);
			long long len = abs(sum[uu] - sum[vv]);
			printf("%lld\n", dist[u] - dist[uu] + dist[v] - dist[vv] + min(sz[lca] - len, len));
		}
	}
	return 0;
}