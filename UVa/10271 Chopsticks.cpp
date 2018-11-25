#include <cstdio>
#include <algorithm>
using namespace std;

const int maxk = 1000+5;
const int maxn = 5000+5;
const int maxl = 32000+5;

int l[maxn];
int dp[maxn][maxn];

int main() {
	int T; scanf("%d", &T);
	int N, K;
	while (T--) {
		scanf("%d%d", &K, &N); K += 8;
		for (int i = N; i >= 1; i--)
			scanf("%d", &l[i]);

		for (int i = 1; i <= N; i++)
			for (int j = 0; j <= K; j++)
				dp[i][j] = 0x3f3f3f3f;

		dp[0][0] = 0;
		for (int i = 1; i <= N; i++) {
			for (int j = 0; 3 * j <= i; j++) {
				dp[i][j] = dp[i-1][j];
				if (i-2 >= 0 && j-1 >= 0)
					dp[i][j] = min(dp[i][j], 
						dp[i-2][j-1] + (l[i]-l[i-1])*(l[i]-l[i-1]));
			}
		}

		printf("%d\n", dp[N][K]);
	}
	return 0;
}