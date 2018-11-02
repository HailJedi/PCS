#include <bits/stdc++.h>

using namespace std;

const int N = 160;
const int K = 30;
const int P = 12345678;
int dp[2][N][K][K];
int n, m, k;

int main() {
	cin >> n >> m >> k;
	dp[0][0][0][0] = 1;
	int t = 0;
	for (int i = 0; i < n + m; i++) {
		t ^= 1;
		memset(dp[t], 0, sizeof(dp[t]));
		for (int j = 0; j <= min(i, m); j++) {
			for (int l = 0; l <= k; l++) {
				for (int p = 0; p <= k; p++) {
					(dp[t][j+1][max(l-1, 0)][p+1] += dp[t^1][j][l][p]) %= P;
					(dp[t][j][l+1][max(p-1, 0)] += dp[t^1][j][l][p]) %= P;
				}
			}
		}
	}
	int ans = 0;
	for (int i = 0; i <= k; i++) {
		for (int j = 0; j <= k; j++) {
			(ans += dp[t][m][i][j]) %= P;
		}
	}
	cout << ans << endl;
	return 0;
}