#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;
const int M = 30 + 5;
const int INF = 0x3f3f3f3f;

int l[N][M], y[N][M];
int n, m;
int p[N];

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	while (cin >> n >> m && n + m) {
		for (int i = 1; i <= m; i++) {
			cin >> p[i];
		}
		memset(l, -INF, sizeof l);
		memset(y, INF, sizeof y);
		
		for (int i = 0; i <= m; i++) {
			l[0][i] = INF;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				l[i][j] = l[i][j-1];
				for (int k = 0; k < i; k++) {
					l[i][j] = max(l[i][j], min(l[k][j-1], p[j]/(i-k)));
				}
			}
		}
		cout << l[n][m] << ' ';
		for (int i = 0; i <= m; i++) {
			y[0][i] = 0;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (l[i][j-1] >= l[n][m]) {
					y[i][j] = y[i][j-1];
				}
				for (int k = 0; k < i; k++) {
					if (min(l[k][j-1], p[j]/(i-k)) >= l[n][m]) {
						y[i][j] = min(y[i][j], y[k][j-1] + p[j]);
					}
				}
			}
		}
		cout << (l[n][m] == 0 ? 0 : y[n][m]) << endl;
	}
	return 0;
}
