#include <cstdio>
#include <algorithm>
#include <cstring>
#define maxn 128
#define maxm 35
#define maxd 250
using namespace std;

int exp[maxn][maxn];
int pit[maxn][maxn];
int dp[2][6][6][6][6];
int sch[maxd];
int N, M, D;
int idx;

bool cmp1(int &a, int &b) {
	return exp[idx][a] > exp[idx][b];
}

bool cmp2(int &a, int &b) {
	return a > b;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &N, &M, &D); D += 10;
		for (int i = 1; i <= M; i++) {
			for (int j = 1; j <= N; j++) {
				scanf("%d", &exp[i][j]);
				pit[i][j] = j;
			}
			idx = i;
			sort(pit[i]+1, pit[i]+1+N, cmp1);
			sort(exp[i]+1, exp[i]+1+N, cmp2);
			// for (int j = 1; j <= 5; j++)
				// printf("pitcher %d against team %d has exp %d\n", pit[i][j], i, exp[i][j]);
		}
		for (int i = 1; i <= D; i++)
			scanf("%d", &sch[i]);

		memset(dp, 0, sizeof(dp));
		int t = 0, ans = 0;
		for (int day = 1; day <= D; day++) {
			memset(dp[t], 0, sizeof(dp[t]));
			if (sch[day] == 0) {
				for (int a = 0; a <= 0; a++) {
					for (int b = 0; b <= 5; b++) {
						for (int c = 0; c <= 5; c++) {
							for (int d = 0; d <= 5; d++) {
								for (int e = 0; e <= 5; e++) {
									dp[t][a][b][c][d] = max(dp[t][a][b][c][d], dp[t^1][b][c][d][e]);
									ans = max(ans, dp[t][a][b][c][d]);
								}
							}
						}
					}
				}
			} else {
				for (int a = 1; a <= 5; a++) {
					for (int b = 0; b <= 5; b++) {
						if (day > 1 && pit[sch[day]][a] == pit[sch[day-1]][b]) 
							continue;
						for (int c = 0; c <= 5; c++) {
							if (day > 2 && pit[sch[day]][a] == pit[sch[day-2]][c])
								continue;
							for (int d = 0; d <= 5; d++) {
								if (day > 3 && pit[sch[day]][a] == pit[sch[day-3]][d]) 
									continue;
								for (int e = 0; e <= 5; e++) {
									if (day > 4 && pit[sch[day]][a] == pit[sch[day-4]][e]) 
										continue;
									dp[t][a][b][c][d] = max(dp[t][a][b][c][d], dp[t^1][b][c][d][e] + exp[sch[day]][a]);
									ans = max(ans, dp[t][a][b][c][d]);
								}
							}
						}
					}
				}
			}
			t ^= 1;
		}
		printf("%.2f\n", (float)ans / 100);
	}
	return 0;
}