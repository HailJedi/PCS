#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 200+5;
const int INF = 1e9;

int que[2][maxn];
int arr[maxn], tim[maxn];
int dp[maxn][maxn][2];
int N, Aidx, Bidx;

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
				dp[i][j][0] = dp[i][j][1] = INF;
			
		dp[0][0][0] = dp[0][0][1] = 0;
		for (int i = 0; i <= Aidx; i++)
			for (int j = 0; j <= Bidx; j++) {
				if (dp[i][j][0] != INF) {
					int start = dp[i][j][0], end = 0;
					for (int k = i+1; k <= Aidx; k++) {
						start = max(start, arr[que[0][k]]);
						end = max(end, start + tim[que[0][k]]);
						dp[k][j][1] = min(dp[k][j][1], end);
						start += 10; end += 10;
					}
				}
				if (dp[i][j][1] != INF) {
					int start = dp[i][j][1], end = 0;
					for (int k = j+1; k <= Bidx; k++) {
						start = max(start, arr[que[1][k]]);
						end = max(end, start + tim[que[1][k]]);
						dp[i][k][0] = min(dp[i][k][0], end);
						start += 10; end += 10;
					}
				}
			}

		printf("%d\n", min(dp[Aidx][Bidx][0], dp[Aidx][Bidx][1]));
	}
	
	return 0;
}