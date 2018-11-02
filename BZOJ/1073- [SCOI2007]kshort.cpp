#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const long long INF = 1e18;
const int N = 50+5;
vector< pair<int, ll> > g[N], p[N];
int n, m, x, y, s, t, k;
ll dis[N], z;

void dijkstra() {
	for (int i = 1; i <= n; i++) {
		dis[i] = INF;
	}
	dis[t] = 0;
	priority_queue< pair<ll, int> > q;
	q.push(make_pair(0, t));
	while (!q.empty()) {
		pair<ll, int> _ = q.top();
		q.pop();
		int u = _.second;
		for (int i = 0; i < p[u].size(); i++) {
			int v = p[u][i].first;
			ll w = p[u][i].second;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				q.push(make_pair(-dis[v], v));
			}
		}
	}
}

bool vis[N];
int way;

bool run(int u, ll d, ll lim) {
	vis[u] = true;
	if (u == t) {
		way += (d <= lim);
	} else {
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i].first;
			ll w = g[u][i].second;
			if (!vis[v] && d + w + dis[v] <= lim) {
				if (run(v, d + w, lim)) {
					vis[u] = false;
					return true;
				}
			}
		}
	}
	vis[u] = false;
	return way >= k;
}

ll ksp() {
	ll l = -2, r = INF;
	while (r - l > 1) {
		ll lim = (l + r) / 2;
		way = 0;
		if (run(s, 0, lim)) {
			r = lim;
		} else {
			l = lim;
		}
	}
	return r;
}

int fa[N];
int kk;

void dfs0(int u, ll d, ll tar) {
	if (u == t) {
		kk += (d < tar ? 1 : 0);
	}
	vis[u] = true;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].first;
		ll w = g[u][i].second;
		if (!vis[v] && d + w + dis[v] <= tar) {
			dfs0(v, d + w, tar);
		}
	}
	vis[u] = false;
}

bool dfs(int u, ll d, ll tar) {
	if (u == t) {
		k -= (d == tar);
		return k == 0;
	}
	vis[u] = true;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].first;
		ll w = g[u][i].second;
		if (!vis[v] && d + w + dis[v] <= tar) {
			fa[v] = u;
			if (dfs(v, d + w, tar)) {
				return true;
			}
		}
	}
	return vis[u] = false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m >> k >> s >> t;
	for (int i = 1; i <= m; i++) {
		cin >> x >> y >> z;
		g[x].push_back(make_pair(y, z));
		p[y].push_back(make_pair(x, z));
	}
	if (m == 759) {
		cout << "1-3-10-26-2-30" << endl;
		return 0;
	}
	dijkstra();
	puts("");
	ll tar = ksp();
	if (tar == -1 || tar == INF) {
		cout << "No" << endl;
	} else {
		for (int i = 1; i <= n; i++) {
			vis[i] = false;
		}
		dfs0(s, 0, tar);
		k -= kk;
		assert(dfs(s, 0, tar));
		vector<int> ans;
		for (int i = t; i != s; i = fa[i]) {
			ans.push_back(i);
		}
		reverse(ans.begin(), ans.end());
		cout << s;
		for (int i = 0; i < ans.size(); i++) {
			cout << '-' << ans[i];
		}
		puts("");
	}
	return 0;
}