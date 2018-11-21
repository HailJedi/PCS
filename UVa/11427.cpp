/*
Created 2018-11-21
"Expect the Expected"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;

double f[N][N];

int main() {
	int T, kase = 0;
	scanf("%d", &T);
	while (T--) {
		int a, b, n;
		scanf("%d/%d %d", &a, &b, &n);
		double p = 1.0 * a / b;
		memset(f, 0, sizeof f);
		f[0][0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= i && j * b <= a * i; j++) {
				f[i][j] += f[i-1][j] * (1 - p);
				if (j > 0) {
					f[i][j] += f[i-1][j-1] * p;
				}
			}
		}
		double prob = 0;
		for (int j = 0; j <= n && j * b <= a * n; j++) {
			prob += f[n][j];
		}
		printf("Case #%d: %d\n", ++kase, (int)(1 / prob));
	}
	return 0;
}
