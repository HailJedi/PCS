/*
Created 2018-10-22
"Garbage Disposal"
A greedy solution
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, k, a, r = 0;
	long long ans = 0;
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a);
		if (r != 0 && a + r < k) {
			ans++;
			r = 0;
		} else {
			ans += (a + r) / k;
			r = (a + r) % k;
		}
	}
	ans += (r != 0);
	printf("%lld\n", ans);
	return 0;
}
