#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 40000+5;
const int maxm = 10000+5;
const int INF = 1e9;

int N, M, D;
int dp[maxn][2];
int weight[maxn];
int sum[maxn];

bool check(int limit) {
	dp[0][0] = 0; dp[0][1] = INF;
	for (int i = 2; i <= N; i += 2) {
		dp[i][0] = dp[i][1] = INF;
		for (int j = 1; j <= D && i - 2*j >= 0; j++) {
			int front = sum[i-j] - sum[i-2*j];
			int back = sum[i] - sum[i-j];
			if (back > limit) break;
			if (front <= limit) {
				dp[i][0] = min(dp[i][0], dp[i-2*j][1] + 1);
				dp[i][1] = min(dp[i][1], dp[i-2*j][0] + 1);
			}
		}
	}
	return dp[N][(M-1)&1] <= M-1;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &N, &M, &D);
		for (int i = 1; i <= N; i++) {
			scanf("%d", &weight[i]);
			sum[i] = sum[i-1] + weight[i];
		}

		if ((M-1) * D < N || N & 1 || 2 * (M-1) > N) { puts("BAD"); continue; }


		int l = 0, r = maxn*maxn;
		while (l + 1 < r) { // (l, r]
			int mid = (l+r)/2;
			if (check(mid)) r = mid;
			else l = mid; 
		}
		printf("%d\n", r);
	}
	return 0;
}