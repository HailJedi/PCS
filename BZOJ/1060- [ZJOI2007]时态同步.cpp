#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 5e5+5;

struct edge {
	int u, v;
	int w;
	edge() {}
	edge(int u, int v, int w) : u(u), v(v), w(w) {}
} e[N*2];

vector<int> g[N];
int n, s, ct, a, b, t;

void addedge(int u, int v, int w) {
	g[u].push_back(++ct);
	e[ct] = edge(u, v, w);
	g[v].push_back(++ct);
	e[ct] = edge(v, u, w);
}

int dist[N], prf[N];

void dfs(int u, int f) {
	prf[u] = dist[u];
	for (int i = 0; i < g[u].size(); i++) {
		edge &eg = e[g[u][i]];
		if (eg.v != f) {
			dist[eg.v] = dist[u] + eg.w;
			dfs(eg.v, u);
			prf[u] = max(prf[u], prf[eg.v]);
		}
	}
}

ll tar, ans;

void dfs2(int u, int bns, int f) {
	for (int i = 0; i < g[u].size(); i++) {
		edge &eg = e[g[u][i]];
		if (eg.v != f) {
			ll plus = tar - (prf[eg.v] + bns);
			ans += plus;
			dfs2(eg.v, bns + plus, u);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> s;
	for (int i = 1; i < n; i++) {
		cin >> a >> b >> t;
		addedge(a, b, t);
	}
	dfs(s, 0);
	tar = *max_element(dist + 1, dist + 1 + n);
	dfs2(s, 0, 0);
	cout << ans << endl;
	return 0;
}