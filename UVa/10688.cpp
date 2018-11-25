#include <bits/stdc++.h>

using namespace std;

const int N = 500 + 5;

int f[N][N];

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int T, n, k, kase = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &k);
		for (int len = 1; len < n; len++) {
			for (int i = 1; i+len <= n; i++) {
				int j = i+len;
				f[i][j] = 1e9;
				for (int mid = i; mid <= j; mid++) {
					f[i][j] = min(f[i][j], f[i][mid-1] + f[mid+1][j] + (k+mid)*(len+1));
				}
			}
		}
		printf("Case %d: %d\n", ++kase, f[1][n]);
	}
	return 0;
}