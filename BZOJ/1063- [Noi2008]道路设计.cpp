#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 1e5+5;
const int LG = 20;
ll f[N][LG][3];
bool c[N][LG][3];
int n, m, mod;
vector<int> g[N];

bool dp(int u, int m, int fa) {
	f[u][m][0] = 1;
	c[u][m][0] = true;
	f[u][m][1] = f[u][m][2] = 0;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (v != fa) {
			dp(v, m, u);
			ll T = (f[v][m-1][0] + f[v][m-1][1] + f[v][m-1][2]) % mod;
			ll G = (f[v][m][0] + f[v][m][1]) % mod;
			bool p = (c[v][m-1][0] || c[v][m-1][1] || c[v][m-1][2]);
			bool k = (c[v][m][0] || c[v][m][1]);
			f[u][m][2] = (f[u][m][2] * T + f[u][m][1] * G) % mod;
			f[u][m][1] = (f[u][m][1] * T + f[u][m][0] * G) % mod;
			f[u][m][0] = (f[u][m][0] * T) % mod;
			c[u][m][2] = (c[u][m][2] & p) || (c[u][m][1] & k);
			c[u][m][1] = (c[u][m][1] & p) || (c[u][m][0] & k);
			c[u][m][0] = c[u][m][0] & p;
		}
	}
	return c[u][m][0] || c[u][m][1] || c[u][m][2];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> mod;
	if (m != n - 1) {
		puts("-1");
		puts("-1");
		return 0;
	}
	int a, b;
	for (int _ = 1; _ <= m; _++) {
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	for (int i = 1; ; i++) {
		if (dp(1, i, -1)) {
			cout << i - 1 << endl;
			cout << (f[1][i][0] + f[1][i][1] + f[1][i][2]) % mod;
			break;
		}
	}

	return 0;
}