/*
Created 2018-10-27
"USACO 2012 January Contest, Gold Division
Problem 3. Bovine Alliance"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const int mod = 1e9 + 7;

bool vis[N];
int v = 0, e = 0;
vector<int> g[N];

int dfs(int u, int f) {
	v++;
	vis[u] = true;
	e += g[u].size();
	for (int w: g[u]) {
		if (!vis[w]) {
			dfs(w, u);
		}
	}
}

int main() {
	freopen("alliance.in", "r", stdin);
	freopen("alliance.out", "w", stdout);
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int ans = 1;
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			v = e = 0;
			dfs(i, -1);
			e /= 2;
			if (e == v - 1) {
				ans = 1LL * ans * v % mod;
			}
			if (e == v) {
				ans = 1LL * ans * 2 % mod;
			}
			if (e > v) {
				ans = 0;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
