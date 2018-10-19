/*
Created 2018-10-19
"NOIP2012 Day1T2"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;

pair<int, int> p[N];
int a, b, n;

int main() {
	scanf("%d %d %d", &n, &a, &b);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &p[i].second, &p[i].first);
	}
	sort(p+1, p+1+n);
	long long ans = 0, prod = a;
	for (int i = 1; i <= n; i++) {
		ans = max(ans, prod / p[i].first);
		prod *= p[i].second;
	}
	printf("%lld\n", ans);
	return 0;
}
