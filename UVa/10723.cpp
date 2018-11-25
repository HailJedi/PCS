#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 30 + 5;
const int INF = 0x3f3f3f3f;

int f[N][N];
long long g[N][N];
char x[N], y[N];

void update(int i, int j, int k, int l) {
	if (f[i][j] == f[k][l] + 1) {
		g[i][j] += g[k][l];
	} else
	if (f[i][j] < f[k][l] + 1) {
		f[i][j] = f[k][l] + 1;
		g[i][j] = g[k][l];
	}
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int T, kase = 0;
	scanf("%d", &T);
	getchar();
	while (T--) {
//		scanf("%s %s", x+1, y+1);
		gets(x+1);
		gets(y+1);
		int n = strlen(x+1);
		int m = strlen(y+1);
		/*
		memset(f, INF, sizeof f);
		f[0][0] = 0;
		f[1][0] = f[0][1] = 1;
		*/
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		for (int i = 0; i <= n; i++) {
			f[i][0] = i;
			g[i][0] = 1;
		}
		for (int i = 0; i <= m; i++) {
			f[0][i] = i;
			g[0][i] = 1;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (x[i] == y[j]) {
					update(i, j, i-1, j-1);
				} else {
					update(i, j, i-1, j);
					update(i, j, i, j-1);
				}
			}
		}
		printf("Case #%d: %d %lld\n", ++kase, f[n][m], g[n][m]);
	}
	return 0;
}