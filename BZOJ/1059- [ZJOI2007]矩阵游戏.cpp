#include <bits/stdc++.h>

using namespace std;

const int N = 233;
int ptn[N];
bool g[N][N], vis[N];
int n, t;

bool find(int x) {
	for (int i = 1; i <= n; i++) {
		if (g[x][i] && !vis[i]) {
			vis[i] = true;
			if (!ptn[i] || find(ptn[i])) {
				ptn[i] = x;
				return true;
			}
		}
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> t;
	while (t--) {
		cin >> n;
		memset(g, 0, sizeof(g));
		memset(ptn, 0, sizeof(ptn));
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> g[i][j];
			}
		}
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			memset(vis, 0, sizeof(vis));
			if (find(i)) {
				cnt++;
			}
		}
		puts(cnt == n ? "Yes" : "No");
	}
	return 0;
}