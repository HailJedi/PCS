/*
Created 2019-1-4
"集合计数"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;
const int mod = 1000000007;

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
	return 1LL * fac[n] * inv[k] % mod * inv[n-k] % mod;
}

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	fac[0] = 1;
	for (int i = 1; i <= n; i++) {
		fac[i] = 1LL * fac[i-1] * i % mod;
	}
	inv[n] = power(fac[n], mod-2);
	for (int i = n; i > 0; i--) {
		inv[i-1] = 1LL * inv[i] * i % mod;
	}
	int ans = 0, pow = 2;
	for (int i = n-k; i >= 0; i--) {
		(ans += 1LL * (i & 1 ? -1 : 1) * C(n-k, i) * (pow - 1) % mod) %= mod;
		pow = 1LL * pow * pow % mod;
	}
	ans = 1LL * ans * C(n, k) % mod;
	if (ans < 0) {
		ans += mod;
	}
	printf("%d\n", ans);
	return 0;
}