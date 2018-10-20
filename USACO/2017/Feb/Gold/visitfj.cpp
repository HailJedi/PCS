/*
Created 2018-10-20
"USACO 2017 February Contest, Gold
Problem 1. Why Did the Cow Cross the Road"
A DP solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;
const int ST = 1000 + 5;
const int INF = 0x3f3f3f3f;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int n, T;
int f[2][N][N], a[N][N];

void update(int &x, int y) {
	if (x > y) {
		x = y;
	}
}

bool in_bound(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

int main() {
	freopen("visitfj.in", "r", stdin);
	freopen("visitfj.out", "w", stdout);
	scanf("%d %d", &n, &T);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	int t = 0, ans = INF;
	memset(f[t], INF, sizeof f[t]);
	f[t][0][0] = 0;
	for (int k = 1; k < ST; k++) {
		memset(f[t^1], INF, sizeof f[t^1]);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (f[t][i][j] != INF) {
					for (int d = 0; d < 4; d++) {
						int x = i + dx[d], y = j + dy[d];
						if (in_bound(x, y)) {
							update(f[t^1][x][y], f[t][i][j] + a[x][y] * (k % 3 == 0) + T);
						}
					}
				}
			}
		}
		update(ans, f[t][n-1][n-1]);
		update(ans, f[t^1][n-1][n-1]);
		t ^= 1;
	}
	printf("%d\n", ans);
	return 0;
}
