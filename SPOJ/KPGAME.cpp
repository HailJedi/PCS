/*
Created 2018-11-29
"A game with probability"
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, t = 0;
		double p, q;
		scanf("%d %lf %lf", &n, &p, &q);
		double f[2], g[2];
		f[t] = 0;
		g[t] = 1;
		n = min(1000, n);
		for (int i = 1; i <= n; i++) {
			t ^= 1;
			if (g[t^1] < f[t^1]) {
				p = 1 - p;
				q = 1 - q;
			}
			f[t] = (p * g[t^1] + q * (1 - p) * f[t^1]) / (p + q - p * q);
			g[t] = (q * f[t^1] + p * (1 - q) * g[t^1]) / (p + q - p * q);
			if (g[t^1] < f[t^1]) {
				p = 1 - p;
				q = 1 - q;
			}
		}
		printf("%.7lf\n", f[t]);
	}
	return 0;
}
