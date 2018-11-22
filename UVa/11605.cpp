/*
Created 2018-11-22
"Lights inside a 3d Grid"
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int X, Y, Z, k, T, kase = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d %d", &X, &Y, &Z, &k);
		double ans = 0;
		for (int x = 0; x < X; x++) {
			for (int y = 0; y < Y; y++) {
				for (int z = 0; z < Z; z++) {
					double p = (2.0 * (x+1) * (X-x) - 1) / X / X;
					p *= ((2.0 * (y+1) * (Y-y) - 1) / Y / Y);
					p *= ((2.0 * (z+1) * (Z-z) - 1) / Z / Z);
					ans += (1 - pow(-2.0 * p + 1, k)) / 2;
				}
			}
		}
		printf("Case %d: %.10lf\n", ++kase, ans);
	}
	return 0;
}