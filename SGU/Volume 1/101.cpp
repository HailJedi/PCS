#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) x.size()

const int N = 233;

int n, u, v, s, cnt;
int deg[7];
int to[N];
char dir[N];
vector<int> path;
int hd[N], nxt[N];
bool mark[N];

void link(int u, int v, char d, int e) {
	to[e] = v; dir[e] = d;
	nxt[e] = hd[u]; hd[u] = e;
}

void dfs(int u, int ef) {
	for (int e = hd[u]; e; e = nxt[e]) {
		int id = e > n ? e - n : e;
		if (mark[id]) continue;
		mark[id] = true;
		dfs(to[e], e);
	}
	path.pb(ef);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &u, &v);
		link(u, v, '+', i);
		link(v, u, '-', i+n);
		deg[u]++; deg[v]++;
	}
	for (int i = 0; i <= 6; i++)
		if (deg[i] & 1) s = i, cnt++;
	if (!(cnt == 0 || cnt == 2)) {
		puts("No solution");
		return 0;
	}
	if (!cnt) for (int i = 0; i <= 6; i++) if (deg[i]) { s = i; break; }
	for (int e = hd[s]; e; e = nxt[e]) {
		int id = e > n ? e - n : e;
		if (mark[id]) continue;
		mark[id] = true;
		dfs(to[e], e);
	}
	if (sz(path) < n) { puts("No solution"); return 0; }
	for (int i = sz(path)-1; ~i; i--) {
		int e = path[i];
		printf("%d %c\n", (e > n ? e - n : e), dir[e]);
	} 
	return 0;
}