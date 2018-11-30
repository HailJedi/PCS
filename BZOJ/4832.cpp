/*
Created 2018-11-30
"[Lydsy1704月赛]抵制克苏恩"
*/

#include <bits/stdc++.h>

using namespace std;

long double f[2][8][8][8];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int k, a, b, c;
		scanf("%d %d %d %d", &k, &a, &b, &c);
		int t = 0;
		memset(f[t], 0, sizeof f[t]);
		for (int i = 1; i <= k; i++) {
			t ^= 1;
			for (int a0 = 0; a0 <= 7; a0++) {
				for (int b0 = 0; a0 + b0 <= 7; b0++) {
					for (int c0 = 0; a0 + b0 + c0 <= 7; c0++) {
						f[t][a0][b0][c0] = 0;
						int all = a0 + b0 + c0 + 1;
						if (a0) {
							f[t][a0][b0][c0] += 1.0 * a0 / all * f[t^1][a0-1][b0][c0];
						}
						if (b0) {
							f[t][a0][b0][c0] += 1.0 * b0 / all * f[t^1][a0+1][b0-1][c0+(a0+b0+c0<7)];
						}
						if (c0) {	
							f[t][a0][b0][c0] += 1.0 * c0 / all * f[t^1][a0][b0+1][c0-(a0+b0+c0==7)];
						}
						f[t][a0][b0][c0] += 1.0 / all * (1 + f[t^1][a0][b0][c0]);
					}
				}
			}
		}
		printf("%.2lf\n", (double)f[t][a][b][c]);
	}
	return 0;
}
