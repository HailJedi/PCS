/*
Created 2018-11-30
"染色"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;

double f[N];

double power(double a, int m) {
	double b = 1;
	for (; m; m >>= 1, a *= a) {
		if (m & 1) {
			b *= a;
		}
	}
	return b;
}

int main() {
	freopen("read.in", "r", stdin);
	int n, m, s, t;
	scanf("%d %d %d %d", &n, &m, &s, &t);
	for (int i = s; i <= t; i++) {
		f[i] = f[i-1] + i - s + 1;
	}
	for (int i = t+1; i <= n; i++) {
		f[i] = f[i-1] + t - s + 1;
	}
	double ans = 0;
	for (int i = 1; i <= n; i++) {
		double t = (f[i-1] + f[n-i]) / f[n];
		ans += 1 - power(t, m);
	}
	printf("%.3lf\n", ans);
	return 0;
}
