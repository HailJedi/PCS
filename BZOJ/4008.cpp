/*
Created 2018-11-30
"[HNOI2015]亚瑟王"
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, r;
		scanf("%d %d", &n, &r);
		vector<double> p(n+1), d(n+1);
		for (int i = 1; i <= n; i++) {
			scanf("%lf %lf", &p[i], &d[i]);
		}
		vector< vector<double> > f(n+1, vector<double>(r+1, 0) );
		f[0][r] = 1;
		for (int i = 0; i < n; i++) {
			double pw = 1;
			for (int j = 0; j <= r; j++) {
				f[i+1][j] += f[i][j] * pw;
				if (j) {
					f[i+1][j-1] += f[i][j] * (1 - pw);
				}
				pw *= (1 - p[i+1]);
			}
		}
		double ans = 0;
		for (int i = 1; i <= n; i++) {
			double P = 0, pw = 1;
			for (int j = 0; j <= r; j++) {
				P += f[i-1][j] * (1 - pw);
				pw *= (1 - p[i]);
			}
			ans += P * d[i];
		}
		printf("%.10lf\n", ans);
	}
	return 0;
}
