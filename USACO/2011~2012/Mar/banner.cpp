/*
Created 2018-10-27
"USACO 2012 March Contest, Gold Division
Problem 1. Large Banner"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

long long n, m, l, r, mod;
vector<int> fac[N];

long long sqr(long long x) {
	return x * x;
}

long long calc(long long lp, long long rp, long long prm) {
	lp = (lp + prm - 1) / prm * prm;
	rp = rp / prm * prm;
	long long terms = (rp - lp) / prm + 1;
	return (m + 1) * terms - (lp + rp) * terms / 2;
}

int main() {
	freopen("banner.in", "r", stdin);
	freopen("banner.out", "w", stdout);
	cin >> n >> m >> l >> r >> mod;
	for (int i = 2; i <= n; i++) {
		if (fac[i].empty()) {
			for (int j = i; j <= n; j += i) {
				fac[j].push_back(i);
			}
		}
	}
	long long ans = 0;
	if (1 == l) {
		ans = (n * (m + 1) + m * (n + 1)) % mod;
	}
	long long lp = min(r, m), rp = min(r, m);
	for (long long i = 1; i <= n; i++) {
		while (lp-1 && sqr(i) + sqr(lp-1) >= sqr(l)) {
			lp--;
		}
		while (rp > lp && sqr(i) + sqr(rp) > sqr(r)) {
			rp--;
		}
		if (sqr(i) + sqr(lp) < sqr(l)) {
			continue;
		}
		if (sqr(i) + sqr(rp) > sqr(r)) {
			continue;
		}
		int tmp = 0;
		for (int s = 0; s < (1 << (int)fac[i].size()); s++) {
			int prm = 1;
			int f = __builtin_parity(s) ? -1 : 1;
			for (int j = 0; j < (int)fac[i].size(); j++) {
				if (s & (1 << j)) {
					prm *= fac[i][j];
				}
			}
			tmp = (tmp + f * calc(lp, rp, prm)) % mod;
		}
		ans = (ans + 2 * (n - i + 1) * tmp) % mod;
	}
	cout << (ans + mod) % mod << endl;
	return 0;
}