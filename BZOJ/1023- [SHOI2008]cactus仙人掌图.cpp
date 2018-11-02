#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int N = 5e4+5;
vector<int> g[N];
int n, m, k, d;
int dis[N], dfn[N], low[N];
int fa[N], f[N], sum[N];
int a[N*2];
int ans;
int q[N*2];

void DP(int u, int v) {
	int n = sum[v] - sum[u] + 1, hd = 1, tl = 1;
	for (int i = v; i != u; i = fa[i]) {
		a[n--] = f[i];
	}
	a[n] = f[u], n = sum[v] - sum[u] + 1;
	for (int i = n + 1; i <= 2 * n; i++) {
		a[i] = a[i - n];
	}
	q[hd] = 1;
	for (int i = 2; i <= n + n / 2; i++) {
		while (hd <= tl && i - q[hd] > n / 2) {
			hd++;
		}
		ans = max(ans, a[i] + a[ q[hd] ] + i - q[hd]);
		while (hd <= tl && a[i] - i >= a[ q[tl] ] - q[tl]) {
			tl--;
		}
		q[++tl] = i;
	}
	for (int i = 2; i <= n; i++) {
		f[u] = max(f[u], a[i] + min(i - 1, n - i + 1));
	}
}

set<int>::iterator it;

void dfs1(int u) {
	dfn[u] = low[u] = ++d;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (v != fa[u]) {
			if (!dfn[v]) {
				fa[v] = u;
				sum[v] = sum[u] + 1;
				dfs1(v);
			}
			low[u] = min(low[u], low[v]);
			if (dfn[u] < low[v]) {
				ans = max(ans, f[u] + f[v] + 1);
				f[u] = max(f[u], f[v] + 1);
			}
		}
	}
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (fa[v] != u && dfn[u] < dfn[v]) {
			DP(u, v);
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	while (m--) {
		scanf("%d", &k);
		int x = 0, y = 0;
		while (k--) {
			scanf("%d", &y);
			if (x != 0) {
				g[x].push_back(y);
				g[y].push_back(x);
			}
			x = y;
		}
	}
	dfs1(1);
	printf("%d\n", ans);
	return 0;
}