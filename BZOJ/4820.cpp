/*
Created 2018-12-11
"[Sdoi2017]硬币游戏"
*/

#pragma C++ optimize(2)

#include <bits/stdc++.h>

using namespace std;

const int N = 300 + 5;

int n, m;
char str[N][N];
int prf[N][N];
long double pw[N];

void solve(vector< vector<long double> > &f) {
	for (int i = 0; i <= n; i++) {
		double t = f[i][i];
		for (int j = 0; j <= n+1; j++) {
			f[i][j] /= t;
		}
		for (int j = 0; j <= n; j++) if (j != i) {
			double t = f[j][i];
			for (int k = i; k <= n+1; k++) {
				f[j][k] -= f[i][k] * t;
			}
		}
	}
}

long double calc(int a, int b) {
	int k = 0;
	for (int i = 1; i <= m; i++) {
		while (k && str[a][k+1] != str[b][i]) {
			k = prf[a][k];
		}
		k += str[a][k+1] == str[b][i];
	}
	if (a == b) {
		k = prf[a][k];
	}
	long double ret = 0;
	while (k) {
		ret += pw[m-k];
		k = prf[a][k];
	}
	return ret;
}

void solve() {
	vector< vector<long double> > f(n+1, vector<long double>(n+2, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			f[i][j] = calc(i, j);
		}
	}
	for (int i = 0; i < n; i++) {
		f[i][i] += 1;
		f[i][n] = -pw[m];
		f[n][i] = 1;
	}
	f[n][n+1] = 1;
	solve(f);
	for (int i = 0; i < n; i++) {
		printf("%.10Lf\n", f[i][n+1]);
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", str[i]+1);
		int k = 0;
		for (int j = 2; j <= m; j++) {
			while (k && str[i][k+1] != str[i][j]) {
				k = prf[i][k];
			}
			k += str[i][k+1] == str[i][j];
			prf[i][j] = k;
		}
	}
	pw[0] = 1;
	for (int i = 1; i < N; i++) {
		pw[i] = pw[i-1] * 0.5;
	}
	solve();
	return 0;
}