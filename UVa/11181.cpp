/*
Created 2018-11-21
"Probability|Given"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 20;

double p[N];
double f[N];

int main() {
	int n, r, kase = 0;
	while (scanf("%d %d", &n, &r) && n) {
		for (int i = 0; i < n; i++) {
			scanf("%lf", &p[i]);
		}
		memset(f, 0, sizeof f);
		double tot = 0;
		for (int i = 0; i < (1 << n); i++) {
			if (__builtin_popcount(i) == r) {
				double prob = 1;
				for (int j = 0; j < n; j++) {
					if ((i >> j) & 1) {
						prob *= p[j];
					} else {
						prob *= (1 - p[j]);
					}
				}
				tot += prob;
				for (int j = 0; j < n; j++) {
					if ((i >> j) & 1) {
						f[j] += prob;
					}
				}
			}
		}
		printf("Case %d:\n", ++kase);
		for (int i = 0; i < n; i++) {
			printf("%.6lf\n", f[i] / tot);
		}
	}
	return 0;
}

