#include <bits/stdc++.h>

using namespace std;

const int N = 1500 + 5;
const int INF = 1e9;

vector<int> g[N];
int f[N][2];

int dp(int u, int fa, int fs) {
	if (f[u][fs] != -1) {
		return f[u][fs];
	}
	f[u][fs] = 1;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (v != fa) {
			f[u][fs] += dp(v, u, 1);
		}
	}
	if (fa == -1 || fs) {
		int sum = 0;
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			if (v != fa) {
				sum += dp(v, u, 0);
			}
		}
		f[u][fs] = min(f[u][fs], sum);
	}
	return f[u][fs];
}	

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	int n;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++) {
			g[i].clear();
		}
		for (int i = 0; i < n; i++) {
			int u, v, k;
			scanf("%d:(%d)", &u, &k);
			while (k--) {
				scanf("%d", &v);
				g[u].push_back(v);
				g[v].push_back(u);
			}
		}
		memset(f, -1, sizeof f);
		cout << dp(0, -1, 0) << endl;
	}
	return 0;
}
