/*
Created 2018-11-21
"To Bet or Not To Bet"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 5;
const int INF = 1e9;

double f[N][N];
int num[N];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int m, t;
		scanf("%d %d", &m, &t);
		num[0] = num[m+1] = 0;
		num[m+2] = -1;
		for (int i = 1; i <= m; i++) {
			char str[20];
			scanf("%s", str);
			if (str[0] == 'L') {
				num[i] = INF;
			} else {
				sscanf(str, "%d", &num[i]);
			}
		}
		memset(f, 0, sizeof f);
		f[0][0] = 1;
		for (int i = 0; i < t; i++) {
			for (int j = 0; j <= m; j++) {
				if (num[j+1] == INF) {
					f[i+2][j+1] += f[i][j] * 0.5;
				} else {
					f[i+1][j+1+num[j+1]] += f[i][j] * 0.5;
				}
				if (num[j+2] == INF) {
					f[i+2][j+2] += f[i][j] * 0.5;
				} else {
					f[i+1][j+2+num[j+2]] += f[i][j] * 0.5;
				}
			}
		}
		double ans = 0;
		for (int i = 0; i <= t; i++) {
			ans += f[i][m+1];
		}
		if (fabs(ans - 0.5) < 1e-7) {
			printf("Push. 0.5000\n");	
		} else if (ans < 0.5) {
			printf("Bet against. %.4lf\n", ans);
		} else {
			printf("Bet for. %.4lf\n", ans);
		}
	}
	return 0;
}
