#include <bits/stdc++.h>

using namespace std;

const int N = 100+5;
const double INF = 1e9;

double f[N][N];
double u[N], sum[N];

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int T;
	cin >> T;
	while (T--) {
		int n, w;
		cin >> n >> w;
		double all = 0;
		for (int i = 1; i <= n; i++) {
			cin >> u[i];
			all += u[i];
		}
		sort(u+1, u+1+n);
		for (int i = 1; i <= n; i++) {
			sum[i] = sum[i-1] + u[n-i+1] / all;
		}
		for (int i = 1; i <= w; i++) {
			for (int j = i; j <= n; j++) {
				f[i][j] = INF;
				if (i == 1) {
					f[i][j] = j * sum[j];
				} else {
					for (int k = j-1; k >= i-1; k--) {
						f[i][j] = min(f[i][j], f[i-1][k] + j * (sum[j] - sum[k]));
					}
				}
			}
		}
		cout << fixed << setprecision(4) << f[w][n] << endl;
	}
	return 0;
}