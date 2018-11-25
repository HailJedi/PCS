#include <bits/stdc++.h>

using namespace std;

const int N = 500 + 5;
const int INF = 0x3f3f3f3f;

int f[N][N][2];
int w[N][N];
int sz[N];
bool done[N];
vector<int> g[N];

void dp(int u) {
	if (done[u]) {
		return;
	}
	sz[u] = 1;
	f[u][1][0] = f[u][1][1] = 0;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		dp(v);
		sz[u] += sz[v];
		for (int j = sz[u]; j > 1; j--) {
			for (int x = min(j, sz[v]); x >= 0; x--) {
				f[u][j][0] = min(f[u][j][0], f[u][j-x][1] + f[v][x][0] + w[u][v]);
				f[u][j][0] = min(f[u][j][0], f[u][j-x][0] + f[v][x][1] + 2 * w[u][v]);
				f[u][j][1] = min(f[u][j][1], f[u][j-x][1] + f[v][x][1] + 2 * w[u][v]);
			}
		}
	}
	done[u] = true;
	return;
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	int kase = 0, n;
	while (cin >> n && n) {
		for (int i = 0; i < n; i++) {
			g[i].clear();
		}
		for (int i = 1; i < n; i++) {
			int u, v, d;
			cin >> u >> v >> d;
			w[v][u] = d;
			g[v].push_back(u);
		}
		memset(f, INF, sizeof f);
		memset(done, false, sizeof done);
		dp(0);
		int q;
		cin >> q;
		cout << "Case " << ++kase << ":" << endl;
		while (q--) {
			int x;
			cin >> x;
			for (int i = n; i >= 0; i--) {
				if (f[0][i][0] <= x) {
					cout << i << endl;
					break;
				}
			}
		}
	}
	return 0;
}
		