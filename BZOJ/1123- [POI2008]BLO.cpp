#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 1e5+5;
const int M = 5e5+5;
int n, m, u, v;
vector<int> g[N];
ll ans[N];
int dfn[N], low[N], sz[N];
int dt;

void dfs(int u) {
	dfn[u] = low[u] = ++dt;
	sz[u] = 1;
	int t = 0;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (dfn[v]) {
			low[u] = min(low[u], dfn[v]);
		} else {
			dfs(v);
			sz[u] += sz[v];
			low[u] = min(low[u], low[v]);
			if (dfn[u] <= low[v]) {
				ans[u] += (ll)t * sz[v];
				t += sz[v];
			}
		}
	}
	ans[u] += (ll)t * (n - 1 - t);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1);
	for (int i = 1; i <= n; i++) {
		cout << (ans[i] + n - 1) * 2 << endl;
	}
	return 0;
}