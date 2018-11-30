/*
Created 2018-11-30
"Little Elephant and Broken Sorting"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;

double f[N][N];
int a[N];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			f[j][i] = a[j] > a[i];
		}
	}
	while (m--) {
		int x, y;
		scanf("%d %d", &x, &y);
		for (int i = 1; i <= n; i++) {
			if (i != x && i != y) {
				f[i][x] = f[i][y] = (f[i][x] + f[i][y]) / 2;
				f[x][i] = f[y][i] = (f[x][i] + f[y][i]) / 2;
			}
		}
		f[x][y] = f[y][x] = (f[x][y] + f[y][x]) / 2;
	}
	double ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = i+1; j <= n; j++) {
			ans += f[i][j];
		}
	}
	printf("%.7lf\n", ans);
	return 0;
}
