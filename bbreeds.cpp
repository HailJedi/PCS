/*
Created 2018-10-29
"USACO 2012 November Contest, Gold
Problem 1. Balanced Cow Breeds"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
const int mod = 2012;

int f[N][N];
int sum[N];
char par[N];

void add(int &x, int y) {
	(x += y) %= mod;
}

int main() {
	freopen("bbreeds.in", "r", stdin);
	freopen("bbreeds.out", "w", stdout);
	scanf("%s", par+1);
	int n = strlen(par+1);
	int sum = 0;
	f[0][1] = 1;
	for (int i = 1; i <= n; i++) {
		int s = par[i] == '(' ? 1 : -1;
		sum += s;
		for (int j = 1; j <= sum+1; j++) {
			add(f[i][j], f[i-1][j-s] + f[i-1][j]);
		}
	}
	printf("%d\n", f[n][1]);
	return 0;
}
