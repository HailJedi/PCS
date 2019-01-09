/*
Created 2019-1-4
"[Jsoi2011]分特产"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 20000 + 5;
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

int a[N];

int main() {
	freopen("read.in", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d", &a[i]);
	}
	fac[0] = 1;
	for (int i = 1; i <= 2*n; i++) {
		fac[i] = 1LL * fac[i-1] * i % mod;
	}
	inv[2*n] = power(fac[2*n], mod-2);
	for (int i = 2*n; i > 0; i--) {
		inv[i-1] = 1LL * inv[i] * i % mod;
	}
	int ans = 0;
	for (int i = 0; i <= n; i++) {
		int p = n-i;
		int temp = i & 1 ? -1 : 1;
		for (int j = 1; j <= m; j++) {
			temp = 1LL * temp * C(a[j]+p-1, p-1) % mod;
		}
		ans = (ans + 1LL * temp * C(n, i)) % mod;
	}
	if (ans < 0) {
		ans += mod;
	}
	printf("%d\n", ans);
	return 0;
}