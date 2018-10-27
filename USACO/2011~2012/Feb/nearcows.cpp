/*
Created 2018-10-27
"USACO 2012 February Contest, Gold Division
Problem 3. Nearby Cows"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const int K = 20 + 5;

int n, k;
int inner[N][K], outer[N][K];
vector<int> g[N];

void dfs(int u, int f) {
	for (int v: g[u]) if (v != f) {
		dfs(v, u);
		outer[v][1] = 1;
		for (int i = 1; i <= k; i++) {
			inner[u][i] += inner[v][i-1];
		}
	}
}

void dfs2(int u, int f) {
	for (int v: g[u]) if (v != f) {
		outer[v][1] = inner[u][0];
		for (int i = 2; i <= k; i++) {
			outer[v][i] = outer[u][i-1] + inner[u][i-1] - inner[v][i-2];
		}
		dfs2(v, u);
	}
}

int main() {
	freopen("nearcows.in", "r", stdin);	
	freopen("nearcows.out", "w", stdout);
	scanf("%d %d", &n, &k);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &inner[i][0]);
	}
	dfs(1, 0);
	dfs2(1, 0);
	for (int i = 1; i <= n; i++) {
		int ans = inner[i][0];
		for (int j = 1; j <= k+1; j++) {
			ans = ans + inner[i][j] + outer[i][j];
		}
		printf("%d\n", ans);
	}
	return 0;
}
	
