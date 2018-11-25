#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;
const int H = 8;
const int INF = 0x3f3f3f3f;

int f[2][N][1<<H][H];

void update(int &x, int y) {
	if (x > y) {
		x = y;
	}
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int n, m, kase = 0;
	while (cin >> n >> m && n) {
		int all = 0;
		memset(f, INF, sizeof f);
		int t = 0;
		for (int i = 1; i <= n; i++) {
			int h;
			cin >> h;
			h -= 25;
			t ^= 1;
			memset(f[t], INF, sizeof f[t]);
			f[t][i-1][1<<h][h] = 1;
			for (int j = 0; j <= min(m, i-1); j++) {
				for (int s = all; s; s = (s-1) & all) {
					for (int k = 0; (1 << k) <= s; k++) {
						if (s & (1 << k)) {
							if (k == h) {
								update(f[t][j][s][k], f[t^1][j][s][k]);
							} else {
								update(f[t][j][s|(1<<h)][h], f[t^1][j][s][k] + 1);
								update(f[t][j+1][s][k], f[t^1][j][s][k]);
							}
						}
					}
				}
			}
			all |= (1 << h);
		}
		int ans = INF;
		for (int s = all; s; s = (s-1) & all) {
			for (int i = 0; i <= m; i++) {
				for (int j = 0; (1 << j) <= s; j++) {
					if (s & (1 << j)) {
						update(ans, f[t][i][s][j] + __builtin_popcount(all ^ s));
					}
				}
			}
		}
		cout << "Case " << ++kase << ": " << ans << endl << endl;
	}
	return 0;
}
		