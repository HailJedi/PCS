/*
Created 2018-11-29
"收集邮票"
*/

#include <bits/stdc++.h>

using namespace std;

double f[2], g[2];

int main() {
	freopen("read.in", "r", stdin);	
	int n;
	scanf("%d", &n);
	int t = 0;	
	f[t] = 0;
	g[t] = 0;
	for (int i = n-1; i >= 0; i--) {
		t ^= 1;
		f[t] = f[t^1] + 1.0 * n / (n - i);
		g[t] = 1.0 * i / (n-i) * f[t] + g[t^1] + f[t^1] + 1.0 * n / (n-i);
	}
	printf("%.2lf\n", g[t]);
	return 0;
}
