#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;

int f[N][2][N];

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, t, m, l;
		scanf("%d %d %d", &n, &t, &m);
		memset(f, 0, sizeof f);
		for (int song = 1; song <= n; song++) {
			scanf("%d%*c", &l);
			int p = song & 1;
			for (int disc = 1; disc <= m; disc++) {
				for (int tim = 1; tim <= t; tim++) {
					f[disc][p][tim] = max(f[disc-1][p][t], f[disc][!p][tim]);
					if (l <= tim) {
						f[disc][p][tim] = max(f[disc][p][tim], max(f[disc-1][!p][t], f[disc][!p][tim-l])+1);
					}
				}
			}
		}
		printf("%d\n", f[m][n&1][t]);
		if (T) {
			printf("\n");
		}
	}
	return 0;
}