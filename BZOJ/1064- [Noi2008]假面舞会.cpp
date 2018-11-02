#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;
const int M = 1e6+5;

vector< pair<int, int> > g[N];
int n, m, u, v;

int d;
int dfn[N], val[N], fa[N];
vector<int> cl;

void dfs(int u, int f) {
	dfn[u] = ++d;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].first, d = g[u][i].second;
		if (v != f) {
			if (!dfn[v]) {
				val[v] = val[u] + d;
				dfs(v, u);
			} else {
				if (val[u] + d != val[v]) {
					cl.push_back(abs(val[u] + d - val[v]));
				}
			}
		}
	}
}

int gcd(int a, int b) {
	return !b ? a : gcd(b, a % b);
}

int dist[N];
int mnd, mxd;
bool vis[N];

void dfs2(int u) {
	vis[u] = true;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].first;
		if (!vis[v]) {
			dist[v] = dist[u] + g[u][i].second;
			mnd = min(mnd, dist[v]);
			mxd = max(mxd, dist[v]);
			dfs2(v);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		g[u].push_back(make_pair(v, 1));
		g[v].push_back(make_pair(u, -1));
	}
	for (int i = 1; i <= n; i++) {
		if (!dfn[i]) {
			dfs(i, 0);
		}
	}
	if (n < 3) {
		cout << -1 << ' ' << -1 << endl;
	} else
	if (cl.empty()) {
		int mx = 0;
		for (int i = 1; i <= n; i++) {
			if (!vis[i]) {
				if (g[i].empty()) {
					mx++;
				} else {
					mnd = 1e9;
					mxd = -1e9;
					dfs2(i);
					if (mnd > mxd) {
						cout << -1 << ' ' << -1 << endl;
						return 0;
					} else {
						mx += mxd - mnd + 1;
					}
				}
			}
		}
		if (mx < 3) {
			cout << -1 << ' ' << -1 << endl;
		} else {
			cout << mx << ' ' << 3 << endl;
		}
	} else {
		int mx = cl[0], mn = -1, p = 0;
		while (p + 1 < cl.size() && cl[p] == 0) {
			p++;
		}
		int minv = cl[p];
		for (int i = 1; i < cl.size(); i++) {
			if (cl[i] != 0) {
				mx = gcd(mx, cl[i]);
				minv = min(minv, cl[i]);
			}
		}
		for (int i = 3; i <= minv; i++) {
			bool ok = true;
			for (int j = 0; j < cl.size(); j++) {
				if (cl[j] % i != 0) {
					ok = false;
					break;
				}
			}
			if (ok) {
				mn = i;
				break;
			}
		}
		if (mn != -1) {
			cout << mx << ' ' << mn << endl;
		} else {
			cout << -1 << ' ' << -1 << endl;
		}
	}
	return 0;
}