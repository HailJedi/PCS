#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
const double INF = 1e18;

double f[N];
double mxh[N][N];
double wsum[N];
double w[N], h[N];

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int n;
	double W;
	while (scanf("%d %lf", &n, &W) == 2 && n) {
		for (int i = 1; i <= n; i++) {
			scanf("%lf %lf", &h[i], &w[i]);
			wsum[i] = wsum[i-1] + w[i];
		}
		for (int i = 1; i <= n; i++) {
			mxh[i][i] = h[i];
			for (int j = i+1; j <= n; j++) {
				mxh[i][j] = max(mxh[i][j-1], h[j]);
			}
		}
		for (int i = 0; i <= n; i++) {
			f[i] = INF;
		}
		f[0] = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = i-1; j >= 0; j--) {
				if (wsum[i] - wsum[j] <= W + 1e-6) {
					f[i] = min(f[i], f[j] + mxh[j+1][i]);
				} else {
					break;
				}
			}
		}
		printf("%.4lf\n", f[n]);
	}
	return 0;
}