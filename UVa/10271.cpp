#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 5000 + 5;
const ll INF = 0x3f3f3f3f3f3f;

ll f[2][N];
ll l[N];

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int T;
	scanf("%d", &T);
	while (T--) {
		int k, n;
		scanf("%d %d", &k, &n);
		k += 8;
		for (int i = n; i >= 1; i--) {
			scanf("%lld", &l[i]);
		}
		for (int j = 0; j <= n; j++) {
			f[1][j] = INF;
		}
		memset(f[0], 0, sizeof f[0]);
		int t = 0;
		for (int i = 1; i <= k; i++) {
			t ^= 1;
			for (int j = 0; j <= n; j++) {
				f[t][j] = INF;
			}
			for (int j = i*3; j <= n; j++) {
				f[t][j] = min(f[t][j-1], f[t^1][j-2] + (l[j]-l[j-1])*(l[j]-l[j-1]));
			}
		}
		printf("%lld\n", f[t][n]);
	}
	return 0;
}