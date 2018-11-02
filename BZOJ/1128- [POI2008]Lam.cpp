#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e3+5;

struct Int {
	static const ll BASE = (ll)1e9;
	int sz;
	ll dig[N];
	Int(int v = 0) : sz(1) {
		memset(dig, 0, sizeof(dig));
		dig[0] = v;
	}

	Int &operator = (const int &v) {
		memset(dig, 0, sizeof(dig));
		sz = 1;
		dig[0] = v;
		return *this;
	}

	void normal_size() {
		sz = N;
		while (sz > 1 && dig[sz-1] == 0) {
			sz--;
		}
	}

	friend Int & operator *= (Int &x, const int &y) {
		ll t = 0;
		for (int i = 0; i < x.sz; i++) {
			x.dig[i] *= y;
		}
		for (int i = 0; i < x.sz || t; i++) {
			x.dig[i] += t;
			t = x.dig[i] / BASE;
			x.dig[i] %= BASE;
		}
		x.normal_size();
		return x;
	}

	friend Int operator - (Int &x, Int &y) {
		int sz = max(x.sz, y.sz);
		Int ret(0);
		for (int i = 0; i < sz; i++) {
			ret.dig[i] = x.dig[i] - y.dig[i];
			if (ret.dig[i] < 0) {
				ret.dig[i] += BASE;
				ret.dig[i + 1]--;
			}
		}
		ret.normal_size();
		return ret;
	}

	friend Int &operator /= (Int &x, const int &y) {
		ll r = 0;
		for (int i = x.sz-1; i >= 0; i--) {
			x.dig[i] += r * BASE;
			r = x.dig[i] % y;
			x.dig[i] /= y;
		}
		x.normal_size();
		return x;
	}

	friend int operator % (Int &x, const int &y) {
		Int t = x;
		t /= y;
		t *= y;
		t = x - t;
		return t.dig[0];
	}

	void print() {
		if (sz == 0) {
			printf("0");
		} else {
			printf("%lld", dig[sz-1]);
			for (int i = sz-2; i >= 0; i--) {
				printf("%09lld", dig[i]);
			}
		}
	}
} f[N][2];

int gcd(int x, int y) {
	return !y ? x : gcd(y, x % y);
}

int p[N];
int n;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &p[i]);
	}
	f[n][0] = f[n][1] = 1;
	for (int i = n-1; i; i--) {
		f[i][0] = f[i+1][0];
		f[i][1] = f[i+1][1];
		int g = gcd(f[i][0] % p[i], p[i]);
		f[i][0] /= g;
		f[i][1] *= p[i] / g;
		if (p[i] != 1) {
			int g = gcd(f[i][1] % (p[i]-1), p[i]-1);
			f[i][0] *= (p[i]-1) / g;
			f[i][1] /= g;
		} else {
			f[i][0] = 0, f[i][1] = 1;
		}
	}
	for (int i = 0; i < n; i++) {
		int g = gcd(f[i+1][0] % p[i], p[i]);
		f[i+1][0] /= g;
		f[i+1][1] *= p[i] / g;
		f[i+1][0].print();
		putchar('/');
		f[i+1][1].print();
		puts("");
	}
	return 0;
}
