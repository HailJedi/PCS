/*
Created 2018-11-21
"So you want to be a 2n-aire?"
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	double t, f[35];
	while (scanf("%d %lf", &n, &t) == 2 && n) {
		f[n] = pow(2, n);
		for (int i = n-1; i >= 0; i--) {
			double p0 = max(t, pow(2, i) / f[i+1]);
			double p1 = (p0 - t) / (1 - t);
			f[i] = p1 * pow(2, i) + (1 - p1) * f[i+1] * (p0 + 1) / 2;
		}
		printf("%.3lf\n", f[0]);
	}
	return 0;
}
