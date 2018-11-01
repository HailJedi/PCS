/*
Created 2018-11-01
"USACO 2012 November Contest, Gold
Problem 3. Balanced Trees"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 40000 + 5;
const int M = 80000 + 5;

vector<int> g[N];
int V[M];
int mk[N];
int f[M][2];
bool vis[N][2];

void update(int &x, int y) {
	x = max(x, y);
}

int solve(int e, int d) {
	int &ret = f[e][d == 1];
	if (ret != -1) {
		return ret;
	}
	int v = V[e];
	if (vis[v][d == 1]) {
		int tmp = 0;
		for (int eg: g[v]) {
			update(f[eg^1][d == 1], tmp);
			update(tmp, mk[v] * d + f[eg][d == 1]);
		}
		reverse(g[v].begin(), g[v].end());
		tmp = 0;
		for (int eg: g[v]) {
			update(f[eg^1][d == 1], tmp);
			update(tmp, mk[v] * d + f[eg][d == 1]);
		}
		reverse(g[v].begin(), g[v].end());
		return ret;
	}
	vis[v][d == 1] = true;	
	ret = max(0, mk[v] * d);
	for (int eg: g[v]) {
		if (e != (eg ^ 1)) {
			update(ret, mk[v] * d + solve(eg, d));
		}
	}
	return ret;
}

int main() {
	freopen("btree.in", "r", stdin);
	freopen("btree.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for (int u = 2, v, eg = -1; u <= n; u++) {
		scanf("%d", &v);
		V[++eg] = v;
		g[u].push_back(eg);
		V[++eg] = u;
		g[v].push_back(eg);
	}
	for (int i = 1; i <= n; i++) {
		char ch[10];
		scanf("%s", ch);
		mk[i] = ch[0] == '(' ? 1 : -1;
	}
	int ans = 0;
	memset(f, -1, sizeof f);
	for (int u = 1; u <= n; u++) {
		for (int e: g[u]) {
			update(ans, min(solve(e, 1), solve(e^1, -1)));
		}
	}
	printf("%d\n", ans);
	return 0;
}
