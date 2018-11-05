/*
Created 2018-11-05
"Recovering BST"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 700 + 5;

int f[N][N][2];
int a[N];
int n;
int g[N][N];

int gcd(int a, int b) {
	return !b ? a : gcd(b, a % b);
}

int solve(int l, int r, int p) {
	if (l > r) {
		return 1;
	}
	if (f[l][r][p] != -1) {
		return f[l][r][p];
	}
	f[l][r][p] = 0;
	for (int i = l; i <= r; i++) {
		if (g[i][p ? r+1 : l-1] > 1) {
			f[l][r][p] |= (solve(l, i-1, 1) && solve(i+1, r, 0));
		}
	}
	return f[l][r][p];
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			g[i][j] = gcd(a[i], a[j]);
		}
	}
	memset(f, -1, sizeof f);
	bool ok = false;
	for (int i = 1; i <= n; i++) {
		ok |= (solve(1, i-1, 1) && solve(i+1, n, 0));
	}
	puts(ok ? "Yes" : "No");
	return 0;
}
