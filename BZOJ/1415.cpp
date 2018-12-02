/*
Created 2018-12-01
"[Noi2005]聪聪和可可"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;

double f[N][N];
int fa[N][N];
int dis[N][N];
vector<int> g[N], G[N][N];

int main() {
	int n, m, C, M;
	scanf("%d %d %d %d", &n, &m, &C, &M);
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		queue<int> q;
		q.push(i);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int j = 0; j < (int)g[u].size(); j++) {
				int v = g[u][j];
				if (v != i && dis[i][v] == 0) {
					dis[i][v] = dis[i][u]+1;
					q.push(v);
					G[v][dis[i][v]].push_back(i);
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		sort(g[i].begin(), g[i].end());
	}
	for (int u = 1; u <= n; u++) {
		for (int v = 1; v <= n; v++) {
			if (u != v) {
				for (int i = 0; i < (int)g[u].size(); i++) {
					int w = g[u][i];
					if (dis[v][w] == dis[v][u] - 1) {
						fa[v][u] = w;
						break;
					}
				}
			}
		}
	}
	for (int u = 1; u <= n; u++) {
		for (int i = 1; i <= 2; i++) {
			for (int j = 0; j < (int)G[u][i].size(); j++) {
				int v = G[u][i][j];
				f[u][v] = 1;
			}
		}
	}
	bool ok = false;
	for (int i = 3; i <= dis[C][M] && !ok; i++) {
		for (int u = 1; u <= n && !ok; u++) {
			for (int j = 0; j < (int)G[u][i].size() && !ok; j++) {
				int v = G[u][i][j];
				int deg = g[v].size();
				int nu = fa[v][fa[v][u]];
				for (int k = 0; k < (int)g[v].size(); k++) {
					int nv = g[v][k];
					f[u][v] += (1 + f[nu][nv]) / (deg+1);
				}
				f[u][v] += (1 + f[nu][v]) / (deg+1);
				if (u == C && v == M) {
					ok = true;
				}
			}
		}
	}
	printf("%.3lf\n", f[C][M]);
	return 0;
}