/*
Created 2018-11-01
"Mysterious Crime"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const int M = 10 + 5;

int n, m;
int perm[M][N];
int pos[M][N];
int p[M];

bool check() {
	int std = perm[1][p[1]];
	for (int i = 2; i <= m; i++) {
		if (perm[i][p[i]] != std) {
			return false;
		}
	}
	return true;
}

int main() {
//	freopen("test.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &perm[i][j]);
			pos[i][perm[i][j]] = j;
		}
	}
	long long ans = 0;
	int lp = 1;
	while (lp <= n) {
		int val = perm[1][lp];
		for (int i = 1; i <= m; i++) {	
			p[i] = pos[i][val];
		}
		int len = 1;
		while (lp + len <= n) {
			int mx = 0;
			for (int i = 1; i <= m; i++) {
				p[i]++;
				mx = max(mx, p[i]);
			}
			if (mx > n) {
				break;
			}
			if (check()) {
				len++;
			} else {
				break;
			}
		}
		lp += len;
		ans += 1LL * (len + 1) * len / 2;
	}
	printf("%lld\n", ans);
	return 0;
}
	
