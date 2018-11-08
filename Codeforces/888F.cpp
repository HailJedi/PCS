/*
Created 2018-11-08
"Connecting Vertices"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 500 + 5;
const int mod = 1e9 + 7;

int a[N][N];
long long f[N][N], d[N][N];

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	for (int i = 0; i < n; i++) {
		f[i][i] = d[i][i] = 1;
	}
	for (int len = 2; len <= n; len++) {
		for (int i = 0; i < n; i++) {
			int j = (i + len - 1) % n;
			for (int p = i; p != j; p = (p + 1) % n) {
				if (a[i][j]) {
					(d[i][j] += f[i][p] * f[(p+1)%n][j] % mod) %= mod;
				}
				(f[i][j] += d[i][(p+1)%n] * f[(p+1)%n][j] % mod) %= mod;
			}
		}
	}
	printf("%lld\n", f[0][n-1]);
	return 0;
}
