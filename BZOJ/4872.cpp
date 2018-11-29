/*
Created 2018-11-29
"[Shoi2017]分手是祝愿"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const int mod = 100003;

vector<int> fac[N];
int lt[N];
int inv[N];
int f[N];

int add(int x, int y) {
	return (x + y) % mod;
}

int mul(int x, int y) {
	return 1LL * x * y % mod;
}

int power(int a, int n) {
	int b = 1;
	for (; n; n >>= 1, a = mul(a, a)) {
		if (n & 1) {
			b = mul(b, a);
		}
	}
	return b;
}

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &lt[i]);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j += i) {
			fac[j].push_back(i);
		}
	}
	int x = 0;
	for (int i = n; i >= 1; i--) {
		if (lt[i]) {
			x++;
			for (int j = 0; j < (int)fac[i].size(); j++) {
				int f = fac[i][j];
				lt[f] ^= 1;
			}
		}
	}
	for (int i = 1; i < N; i++) {
		inv[i] = power(i, mod-2);
	}
	for (int i = 1; i <= k; i++) {
		f[i] = 1;
	}
	f[n] = 1;
	for (int i = n-1; i > k; i--) {
		f[i] = mul(add(n, mul(n-i, f[i+1])), inv[i]);
	}
	int ans = 0;
	for (int i = 1; i <= x; i++) {
		ans = add(ans, f[i]);
	}
	for (int i = 1; i <= n; i++) {
		ans = mul(ans, i);
	}
	printf("%d\n", ans);
	return 0;
}
