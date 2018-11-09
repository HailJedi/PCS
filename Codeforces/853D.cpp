/*
Created 2018-11-09
"Michael and Charging Stations"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 300000 + 5;
const int M = 1000 + 5;
const int INF = 0x3f3f3f3f;

int f[2][M];
int a[N];

void update(int &x, int y) {
	if (x > y) {
		x = y;
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		a[i] /= 100;
	}
	int t = 0;
	memset(f[t], INF, sizeof f[t]);
	f[t][0] = 0;
	for (int i = 0; i < n; i++) {
		memset(f[t^1], INF, sizeof f[t^1]);
		for (int j = 0; j < M; j++) {
			int sal = min(j, a[i+1]);
			update(f[t^1][j-sal], f[t][j] + a[i+1] - sal);
			update(f[t^1][j+a[i+1]/10], f[t][j] + a[i+1]);
		}
		t ^= 1;
	}
	int ans = INF;
	for (int i = 0; i < M; i++) {
		update(ans, f[t][i]);
	}
	printf("%d\n", ans * 100);
	return 0;
}
