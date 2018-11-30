/*
Created 2018-11-30
"[SCOI2008]奖励关"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 15;
const int K = 100 + 5;

double f[2][1<<N];
int pt[N];
int pre[N];

int main() {
	freopen("read.in", "r", stdin);
	int k, n;
	scanf("%d %d", &k, &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &pt[i]);
		int x = 0;
		while (scanf("%d", &x) == 1 && x) {
			pre[i] |= (1 << (x-1));
		}
	}
	int t = 0, all = (1 << n) - 1;
	for (int i = k; i >= 1; i--) {
		t ^= 1;
		for (int j = 0; j <= all; j++) {
			f[t][j] = 0;
			for (int l = 0; l < n; l++) {
				if ((pre[l] & j) == pre[l]) {
					f[t][j] += 1.0 / n * max(f[t^1][j | (1 << l)] + pt[l], f[t^1][j]);
				}	else {
					f[t][j] += 1.0 / n * f[t^1][j];
				}
			}
		}
	}
	printf("%.6lf\n", f[t][0]);
	return 0;
}
