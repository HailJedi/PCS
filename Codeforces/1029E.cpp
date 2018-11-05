/*
Created 2018-11-05
"Tree with Small Distances"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 200000 + 5;

int n;
vector<int> g[N];
int fa[N], dis[N];
bool vis[N];
priority_queue<pair<int, int>> q;

void dfs(int u) {
	for (int v: g[u]) {
		if (v != fa[u]) {
			fa[v] = u;
			dis[v] = dis[u] + 1;
			if (dis[v] > 2) {
				q.push(make_pair(dis[v], v));
			} else {
				vis[v] = true;
			}
			dfs(v);
		}
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1);
	int ans = 0;
	while (!q.empty()) {
		int v = q.top().second;
		q.pop();
		if (vis[v]) {
			continue;
		}
		ans++;
		int p = fa[v];
		for (int u: g[p]) {
			vis[u] = true;
		}
		vis[p] = true;
	}
	printf("%d\n", ans);
	return 0;
}
