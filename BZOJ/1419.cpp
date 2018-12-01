/*
Created 2018-12-01
"Red is good"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 5000 + 5;

double f[N][2];

int main() {
	int R, B;
	scanf("%d %d", &R, &B);
	int t = 0;
	for (int i = 0; i <= R; i++) {
		f[i][t] = i;
	}
	for (int b = 1; b <= B; b++) {
		t ^= 1;
		for (int r = 0; r <= R; r++) {
			f[r][t] = max(0.0, 1.0*r/(r+b)*(f[r-1][t]+1) + 1.0*b/(r+b)*(f[r][t^1]-1));
		}
	}
	printf("%.6lf\n", (int)(f[R][t] * 1000000) / 1000000.0);
	return 0;
}
