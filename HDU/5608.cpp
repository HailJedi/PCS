/*
Created 2018-12-28
"Sum"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000000;
const int mod = 1e9 + 7;
const int inv3 = (mod+1)/3;

int n;
int f[N], mu[N], isp[N];
map<int, int> mp;

int sum(int x) {
	return 1LL * x * (x-1) % mod * (x-2) % mod * inv3 % mod;
}

int F(int x) {
	if (x < N) {
		return f[x];
	}
	if (mp.find(x) != mp.end()) {
		return mp[x];
	}
	mp[x] = 0;
	int ans = 1LL * x * (x-1) % mod * (x-2) % mod * inv3 % mod;
	for (int i = 2, j; i <= x; i = j) {
		j = x / (x / i) + 1;
		(ans -= 1LL * (j - i) * F(n / i) % mod) %= mod;
	}
	mp[x] = ans;
	return ans;
}

int main() {
	freopen("read.in", "r", stdin);
	freopen("write.out", "w", stdout);
	int T;
	scanf("%d", &T);
	for (int i = 0; i < N; i++) {
		isp[i] = 1;
		mu[i] = 1;
	}
	for (int i = 2; i < N; i++) {
		if (isp[i]) {
			mu[i] = -1;
			for (int j = i*2; j < N; j += i) {
				isp[j] = 0;
				if ((j / i) % i == 0) {
					mu[j] = 0;
				} else {
					mu[j] *= -1;
				}
			}
		}
	}
	for (int d = 1; d < N; d++) {
		for (int n = d; n < N; n += d) {
			(f[n] += (1LL * d * d - 3 * d + 2) * mu[n/d] % mod) %= mod;
		}
	}
	for (int i = 1; i < N; i++) {
		(f[i] += f[i-1]) %= mod;
	}
	while (T--) {
		scanf("%d", &n);
		printf("%d\n", (F(n) + mod) % mod);
	}
	return 0;
}