/*
Created 2018-11-27
"Vasya and Maximum Matching"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 300000 + 5;

int mod = 998244353;

void add(long long &x, long long y) {
	(x += y) %= mod;
}

void mul(long long &x, long long y) {
	(x *= y) %= mod;
}

long long power(long long a, long long n) {
	long long b = 1;
	for (; n; n /= 2, mul(a, a)) {
		if (n & 1) {
			mul(b, a);
		}
	}
	return b;
}

long long f[N][3];
vector<int> g[N];

void dfs(int u, int fa) {
	long long prod02 = 1, prod0 = 1;
	if (g[u].size() == 1 && fa != 0) {	
		f[u][1] = 1;
		f[u][0] = 1;
		return;
	}
	for (int v: g[u]) {
		if (v != fa) {
			dfs(v, u);
			mul(prod02, (f[v][0] + f[v][2]) % mod);
			mul(prod0, f[v][0]);
		}
	}
	f[u][0] = prod0;
	f[u][1] = prod02;
	for (int v: g[u]) {
		if (v != fa) {
			add(f[u][2], prod02 * power((f[v][0] + f[v][2]) % mod, mod-2) % mod * f[v][1] % mod);
		}
	}
	add(f[u][0], f[u][2]);
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 0);
	printf("%lld\n", f[1][0]);
	return 0;
}
