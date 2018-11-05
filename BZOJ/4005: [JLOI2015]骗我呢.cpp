/*
Created 2018-11-03
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 10000000 + 5;
const int mod = 1e9 + 7;

int n, m;
int fac[N], inv[N];

int power(int a, int n) {
	int b = 1;
	while (n) {
		if (n & 1) {
			b = 1LL * b * a % mod;
		}
		a = 1LL * a * a % mod;
		n >>= 1;
	}
	return b;
}

int C(int n, int k) {
	if (n < 0 || k < 0) {
		return 0;
	}
	return 1LL * fac[n+k] * inv[n] % mod * inv[k] % mod;
}

void add(int &x, int y) {
	x += y;
	while (x >= mod) {
		x -= mod;
	}
}

void throughA(int &x, int &y) {	
	swap(x, y);
	x--;
	y++;
}

void throughB(int &x, int &y) {
	swap(x, y);
	x += m + 2;
	y -= m + 2;
}

int main() {
	scanf("%d %d", &n, &m);
	fac[0] = 1;
	for (int i = 1; i < N; i++) {
		fac[i] = 1LL * fac[i-1] * i % mod;
	}
	inv[N-1] = power(fac[N-1], mod-2);
	for (int i = N-1; i > 0; i--) {
		inv[i-1] = 1LL * inv[i] * i % mod;
	}
	int ans = C(m+n+1, n);
	int x = m+n+1, y = n;
	while (x >= 0 && y >= 0) {
		throughA(x, y);
		add(ans, mod - C(x, y));
		throughB(x, y);
		add(ans, C(x, y));
	}
	x = m+n+1, y = n;
	while (x >= 0 && y >= 0) {
		throughB(x, y);
		add(ans, mod - C(x, y));
		throughA(x, y);
		add(ans, C(x, y));
	}
	printf("%d\n", ans);
	return 0;
}
