/*
Created 2018-10-29
"USACO 2012 March Contest, Gold Division
Problem 2. Haybale Restacking"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

long long a[N], b[N], c[N];

int main() {
	freopen("restack.in", "r", stdin);
	freopen("restack.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld %lld", &a[i], &b[i]);
		c[i] = c[i-1] + b[i] - a[i];
	}
	sort(c+1, c+1+n);
	long long mid = c[n/2];
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += abs(c[i] - mid);
	}
	printf("%lld\n", ans);
	return 0;
}
