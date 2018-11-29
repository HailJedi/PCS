/*
Created 2018-11-29
"Ilya and Escalator"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 2000 + 5;

double f[N][N];

int main() {
	int n, t;
	double p;
	scanf("%d %lf %d", &n, &p, &t);
	for (int i = 0; i <= n && i <= t; i++) {
		f[t][i] = i;
	}
	for (int i = t-1; i >= 0; i--) {
		for (int j = 0; j <= i && j <= n; j++) {
			if (j < n) {
				f[i][j] = p * f[i+1][j+1] + (1-p) * f[i+1][j];	
			} else {
				f[i][j] = f[i+1][j];
			}
		}
	}
	printf("%.7lf\n", f[0][0]);
	return 0;
}
