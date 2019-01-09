/*
Created 2019-1-6
"已经没有什么好害怕的了"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 2000 + 5;
const int mod = 1e9 + 9;

int n, k;
int f[N][N], ans;
int a[N], b[N], t[N];
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
	freopen("read.in", "r", stdin);
	scanf("%d %d", &n, &k);
	if ((n+k) & 1) {
		puts("0");
		return 0;
	}
	k = (n + k) / 2;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	sort(a+1, a+1+n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &b[i]);
	}
	sort(b+1, b+1+n);
	for (int i = 1; i <= n; i++) {
		t[i] = t[i-1];
		while (t[i] < n && a[i] > b[t[i]+1]) {
			t[i]++;
		}
	}
	f[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			f[i][j] = f[i-1][j];
			if (j && t[i] - j + 1) {
				f[i][j] = (f[i][j] + 1LL * f[i-1][j-1] * (t[i] - j + 1) % mod) % mod;
			}
		}
	}
	fac[0] = 1;
	for (int i = 1; i <= n; i++) {
		fac[i] = 1LL * fac[i-1] * i % mod;
	}
	inv[n] = power(fac[n], mod-2);
	for (int i = n; i; i--) {
		inv[i-1] = 1LL * inv[i] * i % mod;
	}
	for (int i = 1; i <= n; i++) {
		f[n][i] = 1LL * f[n][i] * fac[n-i] % mod;
	}
	for (int i = k; i <= n; i++) {
		ans = (ans + 1LL * ((i - k) & 1 ? -1 : 1) * C(i, k) * f[n][i]) % mod;
	}
	ans = (ans + mod) % mod;
	printf("%d\n", ans);
	return 0;
}