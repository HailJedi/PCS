#include <cstdio>
#include <algorithm>
#define BUF (Aidx+1)
using namespace std;

const int maxn = 200+5;
const int INF = 1e8;

int que[2][maxn];
int arr[maxn], tim[maxn];
int dp[maxn][maxn][2];
int N;
int Aidx, Bidx;

int cost(int i, int j, int zero) {
	if (!i || !(i-BUF)) {
		if (j < BUF) 
			return arr[que[0][j]] + tim[que[0][j]];
		else return arr[que[1][j-BUF]] + tim[que[1][j-BUF]];
	}

	// former	
	int farr, ftim;
 	if (i < BUF) {
 		farr = arr[que[0][i]] - zero;
 		ftim = tim[que[0][i]];
 	} else {
 		farr = arr[que[1][i-BUF]] - zero;
 		ftim = tim[que[1][i-BUF]];
 	}
	// latter
	int larr, ltim;
	if (j < BUF) {
 		larr = arr[que[0][j]] - zero;
 		ltim = tim[que[0][j]];
 	} else {
 		larr = arr[que[1][j-BUF]] - zero;
 		ltim = tim[que[1][j-BUF]];
 	}

 	if ((i < BUF && j < BUF) || (i >= BUF && j >= BUF)) {
 		int setoff = max(larr, 10-min(ltim, ftim));
 		return setoff + ltim;
 	} else {
 		return max(0, larr) + ltim;
 	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		char dir[2]; Aidx = Bidx = 0;
		for (int i = 1; i <= N; i++) {
			scanf("%s%d%d", dir, &arr[i], &tim[i]);
			if (dir[0] == 'A') que[0][++Aidx] = i;
			else que[1][++Bidx] = i;
		}

		for (int i = 0; i <= Aidx; i++)
			for (int j = 0; j <= Bidx; j++)
				for (int k = 0; k <= 1; k++)
					dp[i][j][k] = INF;

		printf("%d\n", cost(0, 1, 0));

		arr[0] = -INF; tim[0] = 0;

		dp[0][0][1] = dp[0][0][0] = 0;
		for (int i = 1; i <= Aidx; i++) 
			dp[i][0][0] = dp[i-1][0][0] + cost(i-1, i, dp[i-1][0][0]);
		for (int j = 1; j <= Bidx; j++)
			dp[0][j][1] = dp[0][j-1][1] + cost(j-1+BUF, j+BUF, dp[0][j-1][1]);

		for (int i = 1; i <= Aidx; i++) {
			for (int j = 1; j <= Bidx; j++) {
				dp[i][j][0] = min(dp[i-1][j][0] + cost(i-1, i, dp[i-1][j][0]), 
								  dp[i-1][j][1] + cost(j+BUF, i, dp[i-1][j][1]));
				dp[i][j][1] = min(dp[i][j-1][0] + cost(i, j+BUF, dp[i][j-1][0]), 
								  dp[i][j-1][1] + cost(j-1+BUF, j+BUF, dp[i][j-1][1]));
			}
		}

		printf("%d\n", min(dp[Aidx][Bidx][0], dp[Aidx][Bidx][1]));
	}
	return 0;
}