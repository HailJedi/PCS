#include <bits/stdc++.h>

using namespace std;

const int N = 20;
const int D = 8;
const int INF = 0x3f3f3f3f;

int f[1<<N][D];
int d[N];

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
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &d[i]);
		}
		memset(f, INF, sizeof f);
		for (int i = 0; i < n; i++) {
			f[1<<i][d[i]] = d[i];
		}
		int all = (1<<n)-1;
		for (int i = 1; i < all; i++) {
			for (int j = 1; j < D; j++) {
				if (f[i][j] != INF) {
					for (int k = 0; k < n; k++) {
						if ((i & (1 << k)) == 0) {
							if (d[k] >= j) {
								update(f[i | (1<<k)][d[k]-j+1], f[i][j] + d[k]-j+1);
							} else {
								update(f[i | (1<<k)][1], f[i][j] + 1);
							}
						}
					}
				}
			}
		}
		int ans = INF;
		for (int i = 1; i < D; i++) {
			ans = min(ans, f[all][i]);
		}
		printf("%d\n", ans);
	}
	return 0;
}