#include <bits/stdc++.h>

using namespace std;

const int K = 50+5;
const int N = 600+5;
int a[N][N], f[N][K], from[N][K], output[K];
int n, k, ans, ans_pos;

int sum(int x1, int y1, int x2, int y2) {
	return a[x2][y2] - a[x1-1][y2] - a[x2][y1-1] + a[x1-1][y1-1];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> k;
	for (int i = 1; i < n; i++) {
		for (int j = i+1; j <= n; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			a[i][j] += a[i-1][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			a[i][j] += a[i][j-1];
		}
	}
	memset(f, 0xef, sizeof(f));
	f[0][0] = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= ::k; j++) {
			for (int k = 0; k < i; k++) {
				int t = sum(k+1, i+1, i, n);
				if (f[k][j-1] + t > f[i][j]) {
					f[i][j] = f[k][j-1] + t;
					from[i][j] = k;
				}
			}
			if (j == ::k && f[i][j] > ans) {
				ans = f[i][j];
				ans_pos = i;
			}
		}
	}
	int t = ans_pos;
	for (int i = ::k; i; i--) {
		output[i] = t;
		t = from[t][i];
	}
	for (int i = 1; i <= ::k; i++) {
		cout << output[i] << ' ';
	}
	cout << endl;
	return 0;
}