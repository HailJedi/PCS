/*
Created 2018-11-05
"[Sdoi2010]地精部落"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 4200 + 5;

int f[2][N][2];

int main() {
	int n, mod;
	scanf("%d %d", &n, &mod);
	int t = 0;
	f[t][1][0] = 1;
	f[t][2][1] = 1;
	for (int i = 3; i <= n; i++) {
		t ^= 1;
		for (int j = 1; j < i; j++) {
			(f[t^1][j][0] += f[t^1][j-1][0]) %= mod;
			(f[t^1][j][1] += f[t^1][j-1][1]) %= mod;
		}
		memset(f[t], 0, sizeof f[t]);
		for (int j = 1; j < i; j++) {
			f[t][j][0] = (f[t^1][i-1][1] - f[t^1][j-1][1]) % mod;
			f[t][j+1][1] = f[t^1][j][0];
		}
	}
	int ans = 0;
	for (int j = 1; j < n; j++) {
		(ans += (f[t][j][0] + f[t][j+1][1])) %= mod;
	}
	(ans += mod) %= mod;
	printf("%d\n", ans);
	return 0;
}
