/*
Created 2018-11-09
"Gotta Go Fast"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 5;
const int T = 5000 + 5;

int f[N], s[N], p[N];
int n, R;
double ex[N][T];

bool check(double mid) {
	for (int i = n; i >= 1; i--) {
		for (int j = R+1; j < T; j++) {
			ex[i+1][j] = mid;
		}
		for (int j = 0; j <= R; j++) {
			double exf = (ex[i+1][j + f[i]] + f[i]) * p[i] / 100.0;
			double exs = (ex[i+1][j + s[i]] + s[i]) * (100 - p[i]) / 100.0;
			ex[i][j] = min(mid, exf + exs);
		}
	}
	return ex[1][0] < mid;
}

int main() {
	scanf("%d %d", &n, &R);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %d", &f[i], &s[i], &p[i]);
	}
	double l = 0, r = 1e10;
	for (int T = 1; T <= 100; T++) {
		double mid = (l + r) / 2;
		if (check(mid)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	printf("%.10lf\n", r);
	return 0;
}
