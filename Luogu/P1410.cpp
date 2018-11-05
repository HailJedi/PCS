/*
Created 2018-11-05
P1410 子序列
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 2000 + 5;
const int INF = 0x3f3f3f3f;

int a[N];
int f[N][2];

void update(int &x, int y) {
	if (x > y) {
		x = y;
	}
}

int main() {
	freopen("test.in", "r", stdin);
	int n;
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
		}
		memset(f, INF, sizeof f);
		f[0][0] = f[0][1] = 0;
		for (int i = 1; i <= n; i++) {
			// aa
			if (a[i-1] < a[i]) {
				update(f[i][0], f[i-1][0]);
			}
			// ab
			if (f[i-1][0] < a[i]) {
				update(f[i][1], a[i-1]);
			}
			// ba
			if (f[i-1][1] < a[i]) {
				update(f[i][0], a[i-1]);
			}
			// bb
			if (a[i-1] < a[i]) {
				update(f[i][1], f[i-1][1]);
			}
		}
		puts(f[n][0] != INF || f[n][1] != INF ? "Yes!" : "No!");
	}
	return 0;
}
