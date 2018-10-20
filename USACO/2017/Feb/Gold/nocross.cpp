/*
Created 2018-10-20
"USACO 2017 February Contest, Gold
Problem 2. Why Did the Cow Cross the Road II"
A DP solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;

int n;
int f[N][N];
int a[N], b[N];

int update(int &x, int y) {
	if (x < y) {
		x = y;
	}
}

int main() {
	freopen("nocross.in", "r", stdin);
	freopen("nocross.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &b[i]);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			update(f[i][j], f[i-1][j]);
			update(f[i][j], f[i][j-1]);
			if (abs(a[i] - b[j]) <= 4) {
				update(f[i][j], f[i-1][j-1] + 1);
			}
		}
	}
	printf("%d\n", f[n][n]);
	return 0;
}
