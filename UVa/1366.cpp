#include <bits/stdc++.h>

using namespace std;

const int N = 500+5;

int mine[2][N][N];
int sum[2][N][N];
int f[N][N];

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	int n, m;
	while (cin >> n >> m && n * m) {
		for (int i = 0; i < 2; i++) {
			for (int j = 1; j <= n; j++) {
				for (int k = 1; k <= m; k++) {
					cin >> mine[i][j][k];
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				sum[0][i][j] = sum[0][i][j-1] + mine[0][i][j];
				sum[1][i][j] = sum[1][i-1][j] + mine[1][i][j];
			}
		}
		memset(f, -1, sizeof f);
		for (int i = 0; i <= max(n, m); i++) {
			f[i][0] = f[0][i] = 0;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				f[i][j] = max(f[i-1][j] + sum[0][i][j], f[i][j-1] + sum[1][i][j]);
			}
		}
		cout << f[n][m] << endl;
	}
	return 0;
}