#include <bits/stdc++.h>

using namespace std;

const int N = 500 + 5;

int d[N];
int f[N][2];

void update(int &x, int y) {
	if (x < y) {
		x = y;
	}
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int n;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 1; i <= n; i++) {
			scanf("%d", &d[i]);
		}
		for (int i = n; i >= 1; i--) {
			f[i][0] = f[i][1] = 1;
			for (int j = n; j > i; j--) {
				if (d[j] <= d[i]) {
					update(f[i][1], f[j][1] + 1);
				}
				if (d[j] >= d[i]) {
					update(f[i][0], f[j][0] + 1);
				}
			}
		}
		int ans = 1;
		for (int i = 1; i <= n; i++) {
			int up = f[i][0], down = f[i][1];
			for (int j = i; j <= n; j++) {
				if (d[j] < d[i]) {
					update(up, f[i][0] + f[j][1]);
				}
				if (d[j] > d[i]) {
					update(down, f[i][1] + f[j][0]);
				}
			}
			update(ans, max(up, down));
		}
		printf("%d\n", ans);
	}
	return 0;
}
		