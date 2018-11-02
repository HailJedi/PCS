#include <bits/stdc++.h>

using namespace std;

const int K = 15;
const int N = 105;
const int M = 3;
int n, m, k;
int mat[M][N];
int f1[N][K], f2[N][N][K];
int sum[M][N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); 
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> mat[j][i];
			sum[j][i] = sum[j][i-1] + mat[j][i];
		}
	}
	if (m == 1) {
		for (int i = 1; i <= n; i++) {
			for (int l = 1; l <= k && l <= i; l++) {
				f1[i][l] = f1[i-1][l];
				for (int j = 1; j < i; j++) {
					f1[i][l] = max(f1[i][l], f1[j][l-1] + sum[1][i] - sum[1][j]);
				}
			}
		}
		cout << f1[n][k] << endl;
	} else {
		for (int i = 1; i <= k; i++) {
			for (int p = 1; p <= n; p++) {
				for (int q = 1; q <= n; q++) {
					f2[p][q][i] = max(f2[p-1][q][i], f2[p][q-1][i]);
					for (int j = 0; j < p; j++) {
						f2[p][q][i] = max(f2[p][q][i], f2[j][q][i-1] + sum[1][p] - sum[1][j]);
					}
					for (int j = 0; j < q; j++) {
						f2[p][q][i] = max(f2[p][q][i], f2[p][j][i-1] + sum[2][q] - sum[2][j]);
					}
					if (p == q) {
						for (int j = 0; j < p; j++) {
							f2[p][q][i] = max(f2[p][q][i], f2[j][j][i-1] + sum[1][p] - sum[1][j] + sum[2][q] - sum[2][j]);
						}
					}
				}
			}
		}
		cout << f2[n][n][k] << endl;
	}
	return 0;
}