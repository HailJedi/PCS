#include <bits/stdc++.h>

using namespace std;

const int N = 250 + 5;;
const int INF = 0x3f3f3f3f;

int f[N][N];
int sum[N];
int sz[N];

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);

	int n;
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++) {
			scanf("%d", &sz[i]);
		}
//		sort(sz+1, sz+1+n);
		for (int i = 1; i <= n; i++) {
			sum[i] = sum[i-1] + sz[i];
		}
		for (int len = 0; len < n; len++) {
			for (int i = 1; i+len <= n; i++) {
				int j = i+len;
				f[i][j] = INF;
				for (int k = i; k <= j; k++) {
					f[i][j] = min(f[i][j], f[i][k-1]+f[k+1][j]+sum[j]-sum[i-1]-sz[k]);
				}
			}
		}
		printf("%d\n", f[1][n]);
	}
	return 0;
}