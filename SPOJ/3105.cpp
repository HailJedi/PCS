/*
Created 2019-1-6
"Mod"
*/
#include <bits/stdc++.h>

using namespace std;

int a, b, p;

int power(int a, long long n) {
	int b = 1;
	while (n) {
		if (n & 1) {
			b = 1LL * b * a % p;
		}
		a = 1LL * a * a % p;
		n /= 2;
	}
	return b;
}

int gcd(int a, int b) {
	return !b ? a : gcd(b, a % b);
}

int bsgs(int a, int b, int p) {
	a %= p, b %= p;
	if (b == 1) {
		return 0;
	}
	int cnt = 0;
	long long t = 1;
	for (int g = gcd(a, p); g != 1; g = gcd(a, p)) {
		if (b % g) {
			return -1;
		}
		p /= g, b /= g, t = t * a / g % p;
		++cnt;
		if (b == t) {
			return cnt;
		}
	}
	map<int, int> hash;
	int m = ceil(sqrt(1.0 * p));
	long long base = b;
	for (int i = 0; i < m; ++i) {
		hash[base] = i;
		base = base * a % p;
	}
	base = power(a, m);
	for (int i = 1; i <= m+1; ++i) {
		t = t * base % p;
		if (hash.count(t)) {
			return i * m - hash[t] + cnt;
		}
	}
	return -1;
}

int main() {
	freopen("read.in", "r", stdin);
	while (scanf("%d %d %d", &a, &p, &b) == 3 && p) {
		int ans = bsgs(a, b, p);
		if (ans != -1) {
			printf("%d\n", ans);
		} else {
			puts("No Solution");
		}
	}
	return 0;
}