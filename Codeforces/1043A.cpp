/*
Created 2018-11-01
"Elections"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;

long long a[N];

int main() {
//	freopen("test.in", "r", stdin);
	int n;
	long long mx = 0, sum = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		mx = max(mx, a[i]);
		sum += a[i];
	}
	int lp = mx-1, rp = 1e9;
	while (rp - lp > 1) {
		int mid = (lp + rp) / 2;
		if (1LL * n * mid - sum > sum) {
			rp = mid;
		} else {
			lp = mid;
		}
	}
	printf("%d\n", rp);
	return 0;
}
