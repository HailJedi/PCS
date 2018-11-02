#include <bits/stdc++.h>

using namespace std;

const int I = 1e3;
const int N = 40;
const int D = 20;
const int SZ = 1e3;

struct INT {
	int v[I], sz;
	INT() { memset(v, 0, sizeof(v)); }
} f[N];

void print(INT x) {
	printf("%d", x.v[x.sz]);
	for (int i = x.sz-1; i >= 1; i--) {
		printf("%03d", x.v[i]);
	}
	puts("");
}

INT operator * (INT a, INT b) {
	INT c;
	c.sz = a.sz + b.sz;
	for (int i = 1; i <= a.sz; i++) {
		for (int j = 1; j <= b.sz; j++) {
			c.v[i+j-1] += a.v[i] * b.v[j];
		}
	}
	for (int i = 1; i <= c.sz; i++) {
		if (c.v[i] >= SZ) {
			c.v[i+1] += c.v[i] / SZ;
			c.v[i] %= SZ;
			if (i == c.sz) {
				c.sz++;
			}
		}
	}
	while (c.sz > 1 && c.v[c.sz] == 0) {
		c.sz--;
	}
	return c;
}

INT operator ^ (INT a, int n) {
	INT c;
	c.sz = 1;
	c.v[1] = 1;
	while (n) {
		if (n & 1) {
			c = c * a;
		}
		a = a * a;
		n >>= 1;
	}
	return c;
}

INT operator + (INT a, int b) {
	a.v[1] += b;
	for (int i = 1; i <= a.sz; i++) {
		if (a.v[i] >= SZ) {
			a.v[i+1] += a.v[i] / SZ;
			a.v[i] %= SZ;
			if (i == a.sz) {
				a.sz++;
			}
		} else {
			break;
		}
	}
	return a;
}

INT operator - (INT a, INT b) {
	for (int i = 1; i <= a.sz; i++) {
		a.v[i] -= b.v[i];
		if (a.v[i] < 0) {
			a.v[i] += SZ;
			a.v[i+1]--;
		}
	}
	while (a.sz > 1 && a.v[a.sz] == 0) {
		a.sz--;
	}
	return a;
}

int n, d;

int main() {
	scanf("%d %d", &n, &d);
	if (d == 0) {
		puts("1");
		return 0;
	}
	f[0].v[1] = 1;
	f[0].sz = 1;
	for (int i = 1; i <= d; i++) {
		f[i] = (f[i-1] ^ n) + 1;
	}
	print(f[d] - f[d-1]);
	return 0;
}