/*
Created 2018-11-21
"Tribles"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;

double p[N], f[N];
int n, k, m, kase;

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &n, &k, &m);
		for (int i = 0; i < n; i++) {
			scanf("%lf\n", &p[i]);
		}
		f[0] = 0, f[1] = p[0];
		for (int i = 2; i <= m; i++) {
			f[i] = 0;
			for (int j = 0; j < n; j++) {
				f[i] += p[j] * pow(f[i-1], j);
			}
		}
		printf("Case #%d: %.7lf\n", ++kase, pow(f[m], k));
	}
	return 0;
}	
