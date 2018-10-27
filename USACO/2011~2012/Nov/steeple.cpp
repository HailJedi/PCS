/*
Created 2018-10-25
"USACO 2011 November Contest, Gold Division
Problem 3. Cow Steeplechase"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 250 + 5;

vector<int> g[N];
int match[N];
bool vis[N];
int mark[N];
int X1[N], Y1[N], X2[N], Y2[N];

bool dfs(int u) {
	for (int v: g[u]) {
		if (!vis[v]) {
			vis[v] = true;
			if (!match[v] || dfs(match[v])) {
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}

int main() {
	freopen("steeple.in", "r", stdin);
	freopen("steeple.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %d %d", &X1[i], &Y1[i], &X2[i], &Y2[i]);
		if (Y1[i] == Y2[i]) {
			mark[i] = 1;
		} else {
			mark[i] = 2;
		}
	}
	for (int i = 1; i <= n; i++) if (mark[i] == 1) {
		for (int j = 1; j <= n; j++) if (mark[j] == 2) {
			if (1LL*(Y1[j]-Y1[i])*(Y2[j]-Y1[i]) <= 0 && 1LL*(X1[i]-X1[j])*(X2[i]-X1[j]) <= 0) {
				g[i].push_back(j);
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		memset(vis, false, sizeof vis);
		ans += dfs(i);
	}
	printf("%d\n", n - ans);
	return 0;
}
