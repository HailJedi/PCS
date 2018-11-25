#include <bits/stdc++.h>

using namespace std;

const int N = 100;

double dist[N][N];
double f[N][N];
double x[N], y[N];

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int n;
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++) {
			scanf("%lf %lf", &x[i], &y[i]);
			for (int j = 1; j <= i; j++) {
				dist[j][i] = sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
			}
		}
		for (int i = n-1; i >= 2; i--) {
			for (int j = i-1; j >= 1; j--) {
				if (i == n-1) {
					f[j][i] = dist[j][n] + dist[i][n];
				} else {
					f[j][i] = min(f[i][i+1] + dist[j][i+1], f[j][i+1] + dist[i][i+1]);
				}
			}
		}
		printf("%.2lf\n", f[1][2] + dist[1][2]);
	}
	return 0;
}