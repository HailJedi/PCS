/*
Created 2018-10-22
A DP solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
const int V = 20000 + 5;
const int mod = 998244353;

int n;
int h[N];
int pre[N][V];
int cnt[V];
long long f[N][2];

int power(int a, int n) {
	int b = 1;
	while (n) {
		if (n & 1) {
			b = 1LL * b * a % mod;
		}
		n >>= 1;
		a = 1LL * a * a % mod;
	}
	return b;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &h[i]);
		for (int j = 0; j < V; j++) {
			pre[i][j] = pre[i-1][j];
		}
		pre[i][h[i-1]] = i-1;
		cnt[h[i]]++;
	}
	int ans = 0;
	for (int i = 0; i < V; i++) {
		if (cnt[i] > 0) {
			ans = (ans + power(2, cnt[i]) - 1) % mod;
		}
	}
	for (int d = -V+1; d < V; d++) if (d != 0) {
		memset(f, 0, sizeof f);
		f[1][1] = 1;
		for (int i = 2; i <= n; i++) {
			f[i][1] = 1;
			f[i][0] = (f[pre[i][h[i]]][1] + f[pre[i][h[i]]][0]) % mod;
			if (h[i] + d >= 0 && h[i] + d < V) {
				f[i][1] = (f[i][1] + f[pre[i][h[i]+d]][1] + f[pre[i][h[i]+d]][0]) % mod;
			}
		}
		for (int i = 1; i <= n; i++) {
			ans = (ans + f[i][1]) % mod;
		}
		ans = (ans - n) % mod;
	}
	ans = (ans + mod) % mod;
	printf("%d\n", ans);
	return 0;
}
