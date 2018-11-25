#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 5000+5;
const int INF = 0x3f3f3f3f;

char x[maxn], y[maxn];
int xlen, ylen;
int dp[maxn][maxn];

bool check(int k) {
	for (int i = 0; i <= xlen; i++)
		for (int j = 0; j <= ylen; j++)
			dp[i][j] = INF;
	dp[0][0] = 0;
	for (int i = 0; i <= xlen; i++) {
		if (dp[i][ylen] <= k)
			dp[i][0] = 0;
		for (int j = 0; j <= ylen; j++) {
			if (dp[i][j] > k) continue;
			if (x[i] == y[j])
				dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j]);
			dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j] + 1);
			dp[i][j+1] = min(dp[i][j+1], dp[i][j] + 1);
			dp[i+1][j] = min(dp[i+1][j], dp[i][j] + 1);
		}
	}

	return dp[xlen][ylen] <= k;
}

int main() {
	// freopen("read.in", "r", stdin);
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%s %s", y, x);
		xlen = strlen(x); ylen = strlen(y);
		int l = -1, r = ylen;
		while (l+1 < r) {
			int mid = (l+r)/2;
			if (check(mid)) r = mid;
			else l = mid;
		}
		printf("%d\n", r);
	}
	return 0;
}