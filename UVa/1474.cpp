#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 4e3+5;
const ll INF = 1e18;

pair<ll, int> loc[N], sh[N];
bool path[N][N];
int ans[N];
ll f[N][N];

void update(ll &x, ll y) {
	if (x > y) {
		x = y;
	}
}

void dfs(int m, int n) {
	if (!m || !n) {
		return;
	}
	ans[loc[n].second] = sh[m].second;
	dfs(m-path[m][n], n-1);
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int n, m;
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++) {
			scanf("%lld", &loc[i].first);
			loc[i].second = i;
		}
		scanf("%d", &m);
		for (int i = 1; i <= m; i++) {
			scanf("%lld", &sh[i].first);
			sh[i].second = i;
		}
		sh[0].first = -2e9;
		sh[m+1].first = 2e9;
		sort(loc+1, loc+1+n);
		sort(sh+1, sh+1+m);
		for (int i = 0; i <= m; i++) {
			for (int j = 0; j <= n; j++) {
				f[i][j] = INF;
			}
		}
		f[0][0] = 0;
		for (int i = 1; i <= m; i++) {
			for (int j = i; j <= n; j++) {
				ll cost = abs(loc[j].first - sh[i].first);
				f[i][j] = min(f[i][j-1], f[i-1][j-1]) + cost;
				path[i][j] = f[i][j-1] >= f[i-1][j-1];
			}
		}
		cout << f[m][n] << endl;
		dfs(m, n);
		for (int i = 1; i < n; i++) {
			printf("%d ", ans[i]);
		}
		printf("%d\n", ans[n]);
	}
	return 0;
}



