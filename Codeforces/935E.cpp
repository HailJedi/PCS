/*
Created 2018-11-07
"Fafa and Ancient Mathematics"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 10000 + 5;
const int M = 100 + 5;
const int INF = 0x3f3f3f3f;

char expr[N];
int f[2][N][M];
int son[N][2];
int sz[N];
int L[N], R[N];
bool isleaf[N];
int p, m, n, id = 1;
int indi;

void build(int u, int l, int r) {
	if (l == r) {
		f[0][u][0] = f[1][u][0] = expr[l] - '0';
		isleaf[u] = true;
	} else {
		son[u][0] = ++id;
		build(son[u][0], l+1, R[l+1]);
		son[u][1] = ++id;
		build(son[u][1], L[r-1], r-1);
		sz[u] = 1 + sz[son[u][0]] + sz[son[u][1]];
	}
}

void dfs(int u) {
	if (isleaf[u]) {
		return;
	}
	if (!isleaf[son[u][0]]) {
		dfs(son[u][0]);
	}
	if (!isleaf[son[u][1]]) {
		dfs(son[u][1]);
	}
	for (int p2 = 0; p2 <= min(sz[u], min(p, m)); p2++) {
		for (int lp = 0; lp <= p2 - indi; lp++) {
			int rp = p2 - lp - indi;
			f[1][u][p2] = max(f[1][u][p2], f[1][son[u][0]][lp] + f[1][son[u][1]][rp]);
			f[0][u][p2] = min(f[0][u][p2], f[0][son[u][0]][lp] + f[0][son[u][1]][rp]);
		}
		for (int lp = 0; lp <= p2 - (!indi); lp++) {
			int rp = p2 - lp - (!indi);
			f[1][u][p2] = max(f[1][u][p2], f[1][son[u][0]][lp] - f[0][son[u][1]][rp]);
			f[0][u][p2] = min(f[0][u][p2], f[0][son[u][0]][lp] - f[1][son[u][1]][rp]);
		}
	}
}

int main() {
	scanf("%s %d %d", expr+1, &p, &m);
	indi = p <= m;
	stack<int> stk;
	n = strlen(expr+1);
	for (int i = 1; i <= n; i++) {
		L[i] = R[i] = i;
		if (expr[i] == ')') {
			L[i] = stk.top();
			R[stk.top()] = i;
			stk.pop();
		}
		if (expr[i] == '(') {
			stk.push(i);
		}
	}
	memset(f[0], INF, sizeof f[0]);
	memset(f[1], -INF, sizeof f[1]);
	build(1, 1, n);
	dfs(1);
	printf("%d\n", f[1][1][min(p, m)]);
	return 0;
}
