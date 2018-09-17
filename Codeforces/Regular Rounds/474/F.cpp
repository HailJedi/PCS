#include <bits/stdc++.h>
#define E 100010
#define N 100010
#define pb push_back

using namespace std;

int fm[E], to[E], val[E];
vector<int> g[N];
int n, m, u, v, w;
bool mark[E];
int ans, dp[N];

void dfs(int u, int lst) {
	if (lst) assert(u == to[lst]);
	dp[u] = dp[fm[lst]] + 1;
	ans = max(ans, dp[u]);
	mark[lst] = true;
	for (int e: g[u]) 
		if (e > lst && val[e] > val[lst]) dfs(to[e], e);
}

int main() {
	val[0] = dp[0] = -1;
	cin >> n >> m;
	for (int e = 1; e <= m; e++) {
		cin >> u >> v >> w;
		g[u].pb(e);
		fm[e] = u; to[e] = v; val[e] = w;
	}
	for (int e = 1; e <= m; e++)
		if (!mark[e]) dfs(fm[e], 0);
	cout << ans << endl;
	return 0;
}