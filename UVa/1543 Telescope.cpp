#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

const double PI = acos(-1);
const int maxn = 40;

double dp[maxn][maxn][maxn];
double area[maxn][maxn][maxn];
double dist[maxn][maxn];
double p[maxn];

int main() {
	int N, M;
	while (scanf("%d%d", &N, &M) == 2 && N) {
		for (int i = 0; i < N; i++)
			scanf("%lf", &p[i]);

		for (int i = 0; i < N; i++)
			for (int j = i+1; j < N; j++) {
				double a = p[j]-p[i];
				if (a > 0.5) a = 1 - a;
				dist[i][j] = dist[j][i] = 2 * sin(a * PI);
			}

		for (int i = 0; i < N; i++)
			for (int j = i+1; j < N; j++)
				for (int k = j+1; k < N; k++) {
					double l1 = dist[i][j], l2 = dist[j][k], l3 = dist[k][i];
					double p = (l1+l2+l3) / 2;
					area[i][j][k] = sqrt(p * (p-l1) * (p-l2) * (p-l3));
				}

		memset(dp, 0, sizeof(dp));
		for (int i = 3; i <= M; i++) 
			for (int j = 0; j < N; j++)
				for (int k = j+1; k < N; k++)
					for (int l = k+1; l < N; l++)
						dp[i][j][l] = max(dp[i][j][l], dp[i-1][j][k] + area[j][k][l]);

		double ans = 0;
		for (int i = 0; i < N; i++)
			for (int j = i+M-1; j < N; j++)
				ans = max(ans, dp[M][i][j]);

		printf("%.6lf\n", ans);
	}
	return 0;
}