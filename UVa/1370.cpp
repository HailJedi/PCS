#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int BUF = 100 + 5;

int tim[2][55];
int o[2][305];
int f[2][305][305];

void update(int &x, int y) {
	if (x > y) {
		x = y;
	}
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, a, b;
		scanf("%d", &n);
		for (int i = 0; i < 2; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%d", &tim[i][j]);
			}
		}
		scanf("%d %d", &a, &b);
		for (int i = 1; i <= a; i++) {
			scanf("%d", &o[0][i]);
		}
		for (int i = 1; i <= b; i++) {
			scanf("%d", &o[1][i]);
		}
		memset(f, INF, sizeof f);
		f[0][0][BUF] = 0;
		int t = 0;
		for (int i = 0; i <= a; i++) {
			memset(f[t^1], INF, sizeof f[t^1]);
			for (int j = 0; j <= b; j++) {
				for (int k = -100 + BUF; k < BUF; k++) {
					update(f[t][j][k+1], f[t][j][k]);
				}
				for (int k = 100 + BUF; k > BUF; k--) {
					update(f[t][j][k-1], f[t][j][k]);
				}
				for (int k = -100 + BUF; k <= 100 + BUF; k++) {
					if (i != a && k <= BUF) {
						if (o[0][i+1] == o[1][j]) {
							update(f[t^1][j][tim[0][o[0][i+1]]+BUF], f[t][j][k] + tim[0][o[0][i+1]]);
						} else {
							update(f[t^1][j][tim[0][o[0][i+1]]+ k ], f[t][j][k] + max(0, tim[0][o[0][i+1]]+k-BUF));
						}
					}
					if (j != b && k >= BUF) {
						if (o[1][j+1] == o[0][i]) {
							update(f[t][j+1][BUF-tim[1][o[1][j+1]]], f[t][j][k] + tim[1][o[1][j+1]]);
						} else {
							update(f[t][j+1][ k -tim[1][o[1][j+1]]], f[t][j][k] + max(0, tim[1][o[1][j+1]]-k+BUF));
						}
					}
				}
			}
			t ^= 1;
		}
		t ^= 1;
		int ans = INF;
		for (int i = -100 + BUF; i <= 100 + BUF; i++) {
			update(ans, f[t][b][i]);
		}
		printf("%d\n", ans);
	}
	return 0;
}


