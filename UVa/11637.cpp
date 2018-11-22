/*
Created 2018-11-22
"Garbage Remembering Exam"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

long double fac[N];
int n, k;

double solve() {
	if (n == 1) {
		return 0;
	} else if (2*k+1 >= n) {
		return n;
	}
	double good = 0;
	for (int i = 1; i <= n; i++) {
		int x = min(k, i-1) + min(k, n-i);
		if (n-1-2*k >= x) {
			good += exp(fac[n-1-2*k] + fac[n-1-x] - fac[n-1] - fac[n-1-2*k-x]);
		}
	}
	return n - good;
}

int main() {
	for (int i = 1; i < N; i++) {
		fac[i] = fac[i-1] + log((long double) i);
	}
	int kase = 0;
	while (scanf("%d %d", &n, &k) == 2 && n) {
		printf("Case %d: %.4lf\n", ++kase, solve());
	}
	return 0;
}
