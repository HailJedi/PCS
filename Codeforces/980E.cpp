#include <bits/stdc++.h>

using namespace std;

#define pb push_back

const int N = 1000010;
const int LG = 23;

int fa[N][LG];
vector<int> g[N];
int n, k;
bool mark[N];
int p[LG];

void dfs(int u) {
	for (int v: g[u]) 
		if (v != fa[u][0]) 
			fa[v][0] = u, dfs(v);
}

int dist(int u) {
	int d = 1;
	for (int i = LG-1; i >= 0; i--)
		if (!mark[fa[u][i]]) d += p[i], u = fa[u][i];
	return d;
}

int push(int u) {
	int d = 0;
	while (!mark[u]) {
		d++;
		mark[u] = true;
		u = fa[u][0];
	}
	return d;
}

int main() {
	for (int i = 0; i < LG; i++) p[i] = 1 << i;
	scanf("%d %d", &n, &k);
	int u, v;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &u, &v);
		g[u].pb(v); g[v].pb(u);
	}
	dfs(n);
	for (int i = 1; i < LG; i++) 
		for (int j = 1; j <= n; j++) 
			fa[j][i] = fa[fa[j][i-1]][i-1];
	mark[0] = mark[n] = true;
	k = n-k-1;
	for (int x = n-1; x >= 1 && k; x--) {
		if (mark[x]) continue;
		int d = dist(x);
		if (d <= k) {
			k -= d;
			int dd = push(x);
		}
	}
	for (int i = 1; i <= n; i++)
		if (!mark[i]) printf("%d ", i);
	puts("");
	return 0;
}
