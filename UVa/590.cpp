#include <bits/stdc++.h>

using namespace std;

const int D = 30;
const int N = 15;
const int K = 1005;
const int INF = 1e9;

int cost[N][N][D];
int rnd[N][N];
int f[K][N];
int n, k;

int dp(int day, int pos) {
	if (f[day][pos] != -1) {
		return f[day][pos];
	}
	f[day][pos] = INF;
	if (day == k) {
		return f[day][pos] = pos == n ? 0 : INF;
	}
	for (int nxt = 1; nxt <= n; nxt++) {
		if (nxt != pos && cost[pos][nxt][day%rnd[pos][nxt]] != 0) {
			f[day][pos] = min(f[day][pos], cost[pos][nxt][day%rnd[pos][nxt]] + dp(day+1, nxt));
		}
	}
	return f[day][pos];
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int kase = 0;
	while (cin >> n >> k && n + k) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (j != i) {
					cin >> rnd[i][j];
					for (int p = 0; p < rnd[i][j]; p++) {
						cin >> cost[i][j][p];
					}
				}
			}
		}
		memset(f, -1, sizeof f);
		int ans = dp(0, 1);
		cout << "Scenario #" << ++kase << endl;
		if (ans != INF) {
			cout << "The best flight costs " << ans << "." << endl;
		} else {
			cout << "No flight possible." << endl;
		}
		cout << endl;
	}
	return 0;
}