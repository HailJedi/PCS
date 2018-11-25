#include <bits/stdc++.h>

using namespace std;

const int N = 100+5;

typedef int ll;

ll a[N], sum[N], f[N][N], g[N][N], d[N][N];
int n;

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	while (cin >> n && n) {
		
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			sum[i] = sum[i-1] + a[i];
		}
		
		for (int i = 1; i <= n; i++) {
				f[i][i] = g[i][i] = d[i][i] = a[i];
		}
		
		for (int l = 1; l < n; l++) {
			for (int i = 1; i + l <= n; i++) {
				int j = i + l;
				int m = min(0, min(f[i+1][j], g[i][j-1]));
				d[i][j] = sum[j] - sum[i-1] - m;
				f[i][j] = min(f[i+1][j], d[i][j]);
				g[i][j] = min(g[i][j-1], d[i][j]);
			}
		}
		
		cout << 2 * d[1][n] - sum[n] << endl;
	}
	
	return 0;
}