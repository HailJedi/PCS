/*
Created 2018-12-02
"Guest Student"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 7;

int a[N];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int k;
		scanf("%d", &k);
		int tot = 0;
		for (int i = 0; i < 7; i++) {
			scanf("%d", &a[i]);
			tot += a[i];
		}
		int week = k / tot;
		week -= week ? 1 : 0;
		tot = k - week * tot;
		int bon = tot ? 14 : 0;
		for (int i = 0; i < 7 && tot; i++) if (a[i]) {
			int t = tot, tt = 0;
			for (int j = i; t; t -= a[j], j = (j+1) % 7, tt++);
			bon = min(bon, tt);
		}
		printf("%d\n", bon + 7 * week);
	}
}
