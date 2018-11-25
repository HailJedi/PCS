#include <iostream>
#include <cstring>
using namespace std;

const int INF = 1e9;
const int maxn = 10000+5;
int dp[2][maxn][2];
int pos[maxn], lim[maxn];
int n;

int main() {
	ios::sync_with_stdio(false);
	while (cin >> n) {
		for (int i = 1; i <= n; i++) 
			cin >> pos[i] >> lim[i];
		memset(dp, 0, sizeof(dp));
		int t = 0;
		for (int i = n-1; i >= 1; i--) {
			for (int j = i+1; j <= n; j++) {
				dp[t][j][0] = min(dp[t^1][j][0] + pos[i+1] - pos[i], 
								  dp[t^1][j][1] + pos[j] - pos[i]);
				if (dp[t][j][0] >= lim[i]) dp[t][j][0] = INF;
				dp[t][j][1] = min(dp[t][j-1][1] + pos[j] - pos[j-1],
								  dp[t][j-1][0] + pos[j] - pos[i]);
				if (dp[t][j][1] >= lim[j]) dp[t][j][1] = INF;
			}
			t ^= 1;
		}
		int ans = min(dp[t^1][n][0], dp[t^1][n][1]);
		if (ans == INF) cout << "No solution\n";
		else cout << ans << endl;
	}

	return 0;
}