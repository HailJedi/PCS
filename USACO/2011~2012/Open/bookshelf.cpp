/*
Created 2018-10-29
"USACO 2012 US Open, Gold Division
Problem 2. Bookshelf"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int w[N], h[N];
int n, l;
long long dp[N];
set<long long> dps;
int width[N];

int main() {
	freopen("bookshelf.in", "r", stdin);
	freopen("bookshelf.out", "w", stdout);
	scanf("%d %d", &n, &l);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &h[i], &w[i]);
	}
	int *wd = width;
	int sz = 1;
	long long sumw = 0;
	for (int i = 1, j = 1; i <= n; i++) {
		for (wd[++sz] = 1; sz >= 1 && h[i] >= h[i-wd[sz]]; sz--) {
			dps.erase(h[i-wd[sz]] + dp[i-wd[sz]-wd[sz-1]]);
			wd[sz-1] += wd[sz];
		}
		dps.insert(h[i] + dp[i-wd[sz]]);
		sumw += w[i];
		for (; sumw > l; j++) {
			sumw -= w[j];
			dps.erase(h[j+wd[0]-1] + dp[j-1]);
			if (--wd[0] == 0) {
				wd++;
				sz--;
			} else {
				dps.insert(h[j+wd[0]] + dp[j]);
			}
		}
		dp[i] = *dps.begin();
	}
	printf("%lld\n", dp[n]);
	return 0;
}
