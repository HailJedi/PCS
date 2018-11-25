#include <bits/stdc++.h>

using namespace std;

const int N = 200 + 5;
const int M = 5000;
const int INF = 1e9;

vector<int> g[N];
int f[N][N];
int A[N];

int dp(int u, int len) {
	if (f[u][len] != -1) {
		return f[u][len];
	}
	f[u][len] = INF;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		f[u][len] = min(f[u][len], (u != A[len]) + dp(v, len-1));
	}
	f[u][len] = min(f[u][len], (u != A[len]) + dp(u, len-1));
	return f[u][len];
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
		for (int i = 1; i <= n; i++) {
			g[i].clear();
		}
		for (int i = 1; i <= m; i++) {
			int u, v;
			cin >> u >> v;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		memset(f, -1, sizeof f);
		int n2;
		cin >> n2;
		for (int i = 1; i <= n2; i++) {
			cin >> A[i];
		}
		for (int i = 1; i <= n; i++) {
			f[i][0] = 0;
		}
		int ans = INF;
		for (int i = 1; i <= n; i++) {
			ans = min(ans, dp(i, n2));
		}
		cout << ans << endl;
	}
	return 0;
}