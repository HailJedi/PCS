/*
Created 2018-11-21
"Crossing Rivers"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 10 + 5;

double ex[N];
int p[N], L[N], v[N];

int main() {
	int n, D, kase = 0;
	while (scanf("%d %d", &n, &D) && n + D) {
		for (int i = 1; i <= n; i++) {
			scanf("%d %d %d", &p[i], &L[i], &v[i]);
		}
		p[n+1] = D;
		ex[0] = p[1];
		for (int i = 1; i <= n; i++) {
			ex[i] = ex[i-1] + 2.0 * L[i] / v[i] + p[i+1] - p[i] - L[i];
		}
		printf("Case %d: %.3lf\n\n", ++kase, ex[n]);
	}
	return 0;
}
