/*
Created 2018-11-24
"Path Counting"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 5000 + 5;
const int mod = 1e9 + 7;

int f[N][2*N];
int a[N], prd[N];
int ans[N*2];

int main() {
	int n;
	scanf("%d", &n);
	prd[1] = 1;
	for (int i = 1; i < n; i++) {
		scanf("%d", &a[i]);
		prd[i+1] = 1LL * prd[i] * a[i] % mod;
	}
	for (int i = n; i >= 1; i--) {
		f[i][0] = 1;
		for (int j = 1; i + j <= n; j++) {
			f[i][j] = 1LL * f[i+1][j-1] * a[i] % mod;
			(ans[j] += 1LL * prd[i] * f[i][j] % mod) %= mod;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 2 * n - 2; j >= 1; j--) {
			f[i][j] = f[i-1][j-1];
			if (i > 1 && j >= 2 && j-2 <= n-i) {
				(f[i][j] += 1LL * f[i][j-2] * (a[i-1] - 1) % mod) %= mod;
			}
			(ans[j] += 1LL * prd[i] * f[i][j] % mod) %= mod;
		}
	}
	for (int i = 1; i <= 2 * n - 2; i++) {
		ans[i] = 1LL * ans[i] * (mod+1) / 2 % mod;
		printf("%d ", ans[i]);
	}
	puts("");
	return 0;
}