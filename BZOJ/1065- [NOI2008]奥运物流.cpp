#include <bits/stdc++.h>

using namespace std;

const double INF = 2e9;
const int N = 60 + 5;
double ks[N][N], f[N][N][N];
int n, m;
double k;
int s[N];
double c[N];
vector<int> g[N];

void init() {
	for (int i = 1; i <= n; i++) {
		g[i].clear();
		for (int j = 0; j <= m; j++) {
			for (int k = 0; k <= i; k++) {
				f[i][j][k] = -INF;
			}
		}
	}
}

void ksp(int u, int d) {
	for (int i = 0; i <= g[u].size(); i++) {
		for (int j = 0; j <= m; j++) {
			ks[i][j] = -INF;
		}
	}
	ks[0][0] = 0;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		for (int j = 0; j <= m; j++) {
			for (int k = 0; k <= j; k++) {
				ks[i+1][j] = max(ks[i+1][j], ks[i][k] + f[v][j-k][d]);
			}
		}
	}
}

void dp(int u) {
	for (int i = 0; i < g[u].size(); i++) {
		dp(g[u][i]);
	}
	ksp(u, 2);
	for (int i = 0; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			f[u][j][i] = ks[g[u].size()][j-1] + c[u]*k;
		}
	}
	for (int i = 0; i <= n; i++) {
		ksp(u, i+1);
		for (int j = 0; j <= m; j++) {
			f[u][j][i] = max(f[u][j][i], ks[g[u].size()][j] + c[u] * pow(k, i));
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> c[i];
	}
	double ans = -1;
	for (int i = s[1], len = 2; i != 1; i = s[i], len++) {
		init();
		for (int j = 2; j <= n; j++) {
			if (i == j) {
				g[1].push_back(j);
			} else {
				g[s[j]].push_back(j);
			}
		}
		dp(1);
		ans = max(ans, f[1][m - (s[i] != 1)][0] / (1 - pow(k, len)));
	}
	cout << fixed << setprecision(2) << ans << endl;
}