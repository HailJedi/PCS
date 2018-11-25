#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;
const int INF = 0x3f3f3f3f;

char x[N], y[N];
int f[N];
int g[N][N];

void update(int &x, int y) {
	if (x > y) {
		x = y;
	}
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	while (scanf("%s %s", x+1, y+1) == 2) {
		int n = strlen(x+1);
		memset(g, INF, sizeof g);
		memset(f, INF, sizeof f);
		for (int i = 1; i <= n; i++) {
			g[i][i] = 1;
		}
		for (int len = 1; len < n; len++) {
			for (int i = 1; i+len <= n; i++) {
				int j = i + len;
				for (int k = i; k < j; k++) {
					update(g[i][j], g[i][k] + g[k+1][j]);
				}
				if (y[i] == y[j]) {
					update(g[i][j], g[i+1][j]);
					update(g[i][j], g[i][j-1]);
				}
			}
		}
		f[0] = 0;
		for (int i = 1; i <= n; i++) {
			if (x[i] == y[i]) {
				update(f[i], f[i-1]);
			}
			for (int j = 0; j < i; j++) {
				update(f[i], f[j] + g[j+1][i]);
			}
		}
		printf("%d\n", f[n]);
	}
	return 0;
}