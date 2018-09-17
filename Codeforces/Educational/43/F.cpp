#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz(x) x.size()
#define s 0
#define t n1+n2+1
#define INF 1e9

const int N = 10100;

struct edge {
	int v, c, f, id;
	edge(int v, int c, int f, int id) : v(v), c(c), f(f), id(id) {}
};

vector<edge> egs;
vector<int> g[N];
vector<int> ans[N];
int n1, n2, m, x1, x2;
int dg[N];

void link(int u, int v, int c, int id) {
	g[u].pb(sz(egs));
	egs.pb(edge(v, c, 0, id));
	g[v].pb(sz(egs));
	egs.pb(edge(u, 0, 0, id));
}

int d[N], que[N], hd, tl;

bool bfs() {
	for (int i = s; i <= t; i++) d[i] = INF;
	hd = tl = 1;
	d[s] = 0;
	que[hd] = s;
	while (hd <= tl) {
		int u = que[hd++];
		for (int e: g[u]) {
			if (egs[e].c == egs[e].f) continue;
			int v = egs[e].v;
			if (d[v] > d[u] + 1) {
				d[v] = d[u] + 1;
				que[++tl] = v;
				if (v == t) break;
			}
		}
	}
	return d[t] < INF;
}

int cur[N];

int dfs(int u, int f) {
	if (u == t || f == 0) return f;
	int vf = 0;
	for (int &i = cur[u]; i < sz(g[u]); i++) {
		int e = g[u][i];
		int v = egs[e].v;
		if (egs[e].c > egs[e].f && d[v] == d[u] + 1) {
			int fl = dfs(v, min(f, egs[e].c-egs[e].f));
			egs[e].f += fl;
			egs[e^1].f -= fl;
			vf += fl;
			f -= fl;
			if (f == 0) break;
		}
	}
	return vf;
}

void dinic() {
	while (bfs())  {
		for (int i = s; i <= t; i++) cur[i] = 0;
		while(dfs(s, INF));
	}
}

void get_residual(int q) {
	for (int u = 1; u <= n1; u++) 
		for (int e: g[u]) {
			if (egs[e].v == s || egs[e].f > 0) continue;
			ans[q].pb(egs[e].id);
		}
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n1 >> n2 >> m;
	for (int i = 1; i <= m; i++) {
		cin >> x1 >> x2;
		dg[x1]++; dg[x2+n1]++;
		link(x1, x2+n1, 1, i);
	}
	int mn = *min_element(dg+1, dg+1+n1+n2);
	for (int i = 1; i <= n1; i++) link(s, i, dg[i]-mn, 0);
	for (int i = n1+1; i <= n1+n2; i++) link(i, t, dg[i]-mn, 0);

	int q = mn;
	while (q) {
		dinic();
		get_residual(q);
		for (int e: g[s]) egs[e].c++;
		for (int e: g[t]) egs[e^1].c++;
		q--;
	}

	for (int i = 0; i <= mn; i++) {
		cout << sz(ans[i]) << ' ';
		for (int e: ans[i]) 
			cout << e << ' ';
		puts("");
	}

	return 0;
}