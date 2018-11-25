#include <bits/stdc++.h>

using namespace std;

const int N = 1e3+5;
const int C = 2000;
const int INF = 1e9;

vector<int> g[N];
int f[N][2];

int dp(int u, int fs, int fa) {
	if (f[u][fs] != -1) {
		return f[u][fs];
	}
	f[u][fs] = C;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (v != fa) {
			f[u][fs] += dp(v, 1, u);
		}
	}
	if (fa != -1 && !fs) {
		f[u][fs]++;
	}
	if (fa == -1 || fs) {
		int sum = fa != -1;
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			if (v != fa) {
				sum += dp(v, 0, u);
			}
		}
		f[u][fs] = min(f[u][fs], sum);
	}
	return f[u][fs];
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int n, m;
		cin >> n >> m;
		for (int i = 0; i < n; i++) {
			g[i].clear();
		}
		for (int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		memset(f, -1, sizeof f);
		int ans = 0;
		for (int i = 0; i < n; i++) {
			if (f[i][0] == -1) {
				dp(i, 0, -1);
				ans += f[i][0];
			}
		}
		cout << ans / C << ' ' << m - ans % C << ' ' << ans % C << endl;
	}
	return 0;
}