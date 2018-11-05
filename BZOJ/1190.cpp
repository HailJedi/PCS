/*
Created 2018-11-03
"[HNOI2007]梦幻岛宝珠"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 101;
const int P = 31;
const int C = 11;

long long f[P][N*C];
int power[P];
int n, W;

void update(long long &x, long long y) {
	x = max(x, y);
}

int calc(int p, int c) {
	return power[p] * c;
}

int main() {
	power[0] = 1;
	for (int i = 1; i < P; i++) {
		power[i] = power[i-1] * 2;
	}
	while (scanf("%d %d", &n, &W) == 2 && n != -1) {
		memset(f, 0, sizeof f);
		for (int i = 1; i <= n; i++) {
			int w, v;
			scanf("%d %d", &w, &v);
			int p = 0;
			while ((w&1) == 0) {
				w >>= 1;
				p++;
			}
			for (int j = 1000; j >= w; j--) {
				update(f[p][j], f[p][j-w] + v);
			}
		}
		for (int i = 0; i < P; i++) {
			for (int j = 1; j < 1000; j++) {
				update(f[i][j], f[i][j-1]);
			}
		}
		long long ans = 0;
		for (int i = 0; i < 1000; i++) {
			if (calc(0, i) <= W) {
				update(ans, f[0][i]);
			}
		}
		for (int i = 1; i < P && power[i] <= W; i++) {
			for (int j = min(1000, W>>i); j >= 0; j--) {
				if (calc(i, j) <= W) {
					for (int k = 0; k <= j; k++) if (k*2+(W>>(i-1)&1) < 1000){
						update(f[i][j], f[i][j-k] + f[i-1][k*2+(W>>(i-1)&1)]);
					}
					update(ans, f[i][j]);
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
