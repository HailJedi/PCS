#include <bits/stdc++.h>

using namespace std;

const int INF = 2e9;
const int N = 1e3+5;
const int M = 1e4+5;
int n, m, S, T;

struct edge {
	int u, v, w, c;
	edge(int u, int v, int w, int c) : u(u), v(v), w(w), c(c) {}
	edge() {}
} eg[M*5];

vector<int> g[N];
int ct;
int c[N], pr[N], f[N];
bool vis[N];

bool bfs(int &ans) {
	for (int i = S; i <= T; i++) {
		c[i] = INF;
		vis[i] = false;
	}
	c[S] = 0;
	f[S] = INF;
	queue<int> q;
	q.push(S);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = false;
		for (int i = 0; i < g[u].size(); i++) {
			edge &e = eg[g[u][i]];
			if (e.c > 0 && c[e.v] > c[u] + e.w) {
				c[e.v] = c[u] + e.w;
				pr[e.v] = g[u][i];
				f[e.v] = min(f[u], e.c);
				if (!vis[e.v]) {
					q.push(e.v);
					vis[e.v] = true;
				}
			}
		}
	}
	if (c[T] == INF) {
		return false;
	}
	ans += f[T] * c[T];
	int u = T;
	while (u != S) {
		eg[pr[u]].c -= f[T];
		eg[pr[u] ^ 1].c += f[T];
		u = eg[pr[u]].u;
	}
	return true;
}

void addedge(int u, int v, int w, int c) {
	g[u].push_back(ct);
	eg[ct++] = edge(u, v, w, c);
	g[v].push_back(ct);
	eg[ct++] = edge(v, u, -w, 0);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	S = 0, T = n + 2;
	int lst = 0, a;
	for (int i = 1; i <= n; i++) {
		cin >> a;
		if (a > lst) {
			addedge(S, i, 0, a - lst);
		}
		if (a < lst) {
			addedge(i, T, 0, lst - a);
		}
		addedge(i + 1, i, 0, INF);
		lst = a;
	}
	addedge(n + 1, T, 0, lst);
	int s, t, c;
	for (int i = 1; i <= m; i++) {
		cin >> s >> t >> c;
		addedge(s, t + 1, c, INF);
	}
	int ans = 0;
	while (bfs(ans));
	cout << ans << endl;
	return 0;
}