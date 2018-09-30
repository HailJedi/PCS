#include <bits/stdc++.h>

#define N 300010
#define M 30
#define all(x) x.begin(), x.end()
#define sz(x) x.size()
#define pii pair<int, int>
#define eb emplace_back
#define fs first
#define sc second

using namespace std;

typedef long long ll;

vector<int> g[N], ch[N];
vector<pii> up[N];
int p[N], dp[N][M], val[N];
int u, v, n;
ll ans;

void dfs1(int u, int f) {
	p[u] = f;
	for (int v: g[u]) if (v != f) {
		ch[u].eb(v); dfs1(v, u);
	}
}

void dfs2(int u) {
	for (int v: ch[u]) dfs2(v);
	auto &_dp = dp[u];
	_dp[1] = n;
	for (int k = 2; k < M; k++) {
		vector<int> hp;
		for (int v: ch[u]) 
			if (dp[v][k-1]) hp.eb(dp[v][k-1]);
		sort(all(hp), greater<int>());
		for (int s = sz(hp)-1; s > 0; s--)
			if (hp[s] >= s+1) {
				_dp[k] = s+1; break;
			}
		if (_dp[k]) up[_dp[k]].eb(u, k);
	}
}

int dfs3(int u) {
	if (!sz(ch[u])) {
		ans++; return 1;
	}
	int mx = 0;
	for (int v: ch[u])
		mx = max(mx, dfs3(v));
	ans += mx + 1;
	return mx + 1;
}

int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		cin >> u >> v;
		g[u].eb(v);
		g[v].eb(u);
	}

	dfs1(1, 0);
	fill_n(&dp[0][0], N*M, 0);
	dfs2(1);
	dfs3(1);
	ll add = n;
	fill_n(val, N, 1);

	for (int k = n; k > 1; k--) {
		for (auto e: up[k]) {
			int u = e.fs, v = e.sc;
			while (u && val[u] < v) {
				add += v - val[u];
				val[u] = v;
				u = p[u];
			}
		}
		ans += add;
	}

	cout << ans << endl;

	return 0;
}