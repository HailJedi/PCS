#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 300010;

ll n, f, b;
vector< vector<int> > g;
int dir[2];

bool dfs1(int u, int fa) {
	if (u == b) return dir[1] = fa, true;
	for (auto v: g[u]) if (v != fa) 
		if (dfs1(v, u)) return dir[0] = v, true;
	return false;
}

ll sz[N];

void dfs2(int u, int fa) {
	sz[u] = 1;
	for (auto v: g[u]) if (v != fa) {
		dfs2(v, u);
		sz[u] += sz[v];
	}
}

int main() {
	scanf("%lld %lld %lld", &n, &f, &b);
	g.resize(n+1);
	int u, v;
	for (int i = 1; i <= n-1; i++) {
		scanf("%d %d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs1(f, 0);
	dfs2(f, dir[0]);
	dfs2(b, dir[1]);
	if (n >= 2) cout << (n-1) * n - sz[f] * sz[b] << endl;
	else puts("0");
	return 0;
}