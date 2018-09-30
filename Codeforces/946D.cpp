#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 510;
char str[N];
int pos[N][N];
int idx[N], sum[N], sump[N];
int dp[N][N], minv[N][N];
int n, m, k;

int main() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		scanf("%s", str+1);
		for (int j = 1; j <= m; j++)
			if (str[j] == '1') pos[i][++idx[i]] = j;
		sum[i] = sum[i-1] + idx[i];
		sump[i] = sump[i-1];
		if (idx[i]) sump[i] += pos[i][idx[i]]-pos[i][1]+1;
	}
	if (!k) return printf("%d\n", sump[n]), 0;
	memset(dp, INF, sizeof(dp));
	memset(minv, INF, sizeof(minv));
	for (int i = 0; i <= n; i++) {
		dp[i][0] = sump[i];
		for (int j = sum[i]; j <= k; j++)
			dp[i][j] = 0;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= idx[i]; j++) {
			if (!j) minv[i][j] = 0;
			else for (int p = 1; p+j-1 <= idx[i]; p++)
				minv[i][j] = min(minv[i][j], pos[i][p+j-1]-pos[i][p]+1);
		}
	}
	for (int i = 1; i <= n; i++) 
		for (int j = 0; j <= min(sum[i], k); j++) 
			for (int l = max(0, idx[i]-j); l <= idx[i]; l++) 
				dp[i][j] = min(dp[i][j], dp[i-1][j-(idx[i]-l)] + minv[i][l]);
	cout << dp[n][min(sum[n], k)] << endl;
	return 0;
}