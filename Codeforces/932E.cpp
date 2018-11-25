/*
Created 2018-11-25
"Team Work"
*/

#include <bits/stdc++.h>

using namespace std;

const int K = 5000 + 5;
const int mod = 1e9 + 7;

int f[K][K];

int power(int a, int n) {
	int b = 1;
	for (; n; n >>= 1, a = 1LL * a * a % mod) {
		if (n & 1) {
			b = 1LL * b * a % mod;
		}
	}
	return b;
}

int solve(int step, int a, int b) {
	if (a < 0 || b < 0) {
		return 0;
	}
	if (f[step][a] != -1) {
		return f[step][a];
	}
	if (step == 0) {
		return f[step][a] = power(2, b);
	}
	return f[step][a] = (1LL * a * solve(step-1, a, b) % mod + 1LL * b * solve(step-1, a+1, b-1) % mod) % mod;
}

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	memset(f, -1, sizeof f);
	printf("%d\n", solve(k, 0, n));
	return 0;
}