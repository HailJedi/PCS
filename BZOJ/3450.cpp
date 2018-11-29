/*
Created 2018-11-29
"Easy"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 300000 + 5;

char str[N];
double exlen[N], expt[N];

int main() {
	int n;
	scanf("%d %s", &n, str+1);
	for (int i = 1; i <= n; i++) {
		if (str[i] == 'o') {
			exlen[i] = exlen[i-1] + 1;
			expt[i] = expt[i-1] + 2 * exlen[i-1] + 1;
		} else 
		if (str[i] == 'x') {
			exlen[i] = 0;
			expt[i] = expt[i-1];
		} else {
			exlen[i] = (exlen[i-1] + 1) / 2;
			expt[i] = expt[i-1] + (2 * exlen[i-1] + 1) / 2;
		}
	}
	printf("%.4lf\n", expt[n]);
	return 0;
}
