/*
Created 2019-1-6
"combination"
*/

#include <bits/stdc++.h>

using namespace std;

const int mod = 10007;

int fac[mod], inv[mod];

int power(int a, int n) {
	int b = 1;
	while (n) {
		if (n & 1) {
			b = b * a % mod;
		}
		a = a * a % mod;
		n >>= 1;
	}
	return b;
}

int C(int n, int k) {
	if (k > n) {
		return 0;
	}
	return fac[n] * inv[k] % mod * inv[n-k] % mod;
}

int main() {
	freopen("read.in", "r", stdin);
	fac[0] = 1;
	for (int i = 1; i < mod; ++i) {
		fac[i] = fac[i-1] * i % mod;
	}
	inv[mod-1] = power(fac[mod-1], mod-2);
	for (int i = mod-1; i; --i) {
		inv[i-1] = inv[i] * i % mod;
	}
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, k;
		scanf("%d %d", &n, &k);
		int ans = 1;
		while (n) {
			(ans *= C(n % mod, k % mod)) %= mod;
			n /= mod;
			k /= mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}