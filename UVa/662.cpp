#include <bits/stdc++.h>

using namespace std;

const int N = 200 + 5;
const int K = 30 + 5;
const int INF = 1e9;

int d[N], sum[N];
int cost[N][N], mid[N][N];
int f[N][K];

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);

	int n, k, kase = 0;
	while (scanf("%d %d", &n, &k) == 2 && n + k) {
		for (int i = 1; i <= n; i++) {
			scanf("%d", &d[i]);
			sum[i] = sum[i-1] + d[i];
		}
		for (int i = 1; i <= n; i++) {
			int p = i;
			for (int j = i+2; j <= n; j++) {
				while (d[p] - d[i] < d[j] - d[p]) {
					p++;
				}
				mid[i][j] = p;
				cost[i][j] = (sum[p-1]-sum[i-1]) - d[i] * (p-i) + d[j] * (j-p+1) - (sum[j]-sum[p-1]);
			}
		}
		for (int i = 1; i <= n; i++) {
			mid[0][i] = 1;
			mid[i][n+1] = n+1;
			mid[i][i+1] = i+1;
		}
		for (int i = 1; i <= n; i++) {
			f[i][1] = d[i] * i - sum[i];
		}
		for (int i = 2; i <= k; i++) {
			for (int j = i; j <= n; j++) {
				f[j][i] = INF;
				for (int p = i-1; p < j; p++) {
					f[j][i] = min(f[j][i], f[p][i-1] + cost[p][j]);
				}
			}
		}
		int ans = INF, p = -1;
		for (int i = k; i <= n; i++) {
			int cand = f[i][k] + (sum[n]-sum[i-1]) - d[i] * (n-i+1);
			if (cand < ans) {
				ans = cand;
				p = i;
			}
		}
		vector<int> pos;
		pos.push_back(p);
		while (--k) {
			for (int i = p-1; i >= k; i--) {
				if (f[i][k] + cost[i][p] == f[p][k+1]) {
					p = i;
					break;
				}
			}
			pos.push_back(p);
		}
		pos.push_back(0);
		reverse(pos.begin(), pos.end());
		pos.push_back(n+1);
		int depot = 0;
		printf("Chain %d\n", ++kase);
		for (int i = 1; i < pos.size()-1; i++) {
			int lp = mid[pos[i-1]][pos[i]], rp = mid[pos[i]][pos[i+1]];
			printf("Depot %d at restaurant %d serves restaurant%s %d", ++depot, pos[i], lp == rp-1 ? "" : "s", lp);
			if (lp != rp-1) {
				printf(" to %d", rp-1);
			}
			printf("\n");
		}
		printf("Total distance sum = %d\n\n", ans);
	}
	return 0;
}