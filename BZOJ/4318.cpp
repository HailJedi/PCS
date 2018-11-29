/*
Created 2018-11-29
"OSU!"
*/

#include <bits/stdc++.h>

using namespace std;

int main() {	
	int n;
	double p, l1 = 0, l2 = 0, ans = 0;
	scanf("%d", &n);
	while (n--) {
		scanf("%lf", &p);
		ans += (3 * l2 + 3 * l1 + 1) * p;
		l2 = (l2 + 2 * l1 + 1) * p;
		l1 = (l1 + 1) * p;
	}
	printf("%.1lf\n", ans);
	return 0;
}
