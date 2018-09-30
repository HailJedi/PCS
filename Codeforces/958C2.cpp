#include <bits/stdc++.h>

using namespace std;

const int N = 20010;
const int K = 100;
const int P = 100;
const int INF = 1e5;
int n, k, p, sum[N], dp[N][K], f[P][K];

int main() {
	scanf("%d %d %d", &n, &k, &p);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &sum[i]);
		(sum[i] += sum[i-1]) %= p;
	}
	for (int i = 0; i < P; i++)
		for (int j = 0; j < K; j++) f[i][j] = -INF;
	f[0][0] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= k; j++)
			for (int m = 0; m < p; m++) {
				dp[i][j] = max(dp[i][j], f[m][j-1]+(sum[i]-m+p)%p);
				f[sum[i]][j] = max(f[sum[i]][j], dp[i][j]);
			}
	printf("%d\n", dp[n][k]);
	return 0;
}