#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
const int M = 50000 + 6;

struct Edge {
	Edge *next;
	int u, v;
	void *operator new(size_t, Edge *next, int u, int v) {
		static Edge pool[M*100], *p = pool;
		Edge *ret = p++;
		ret->next = next;
		ret->u = u;
		ret->v = v;
		return ret;
	}
} *head[N], *thead[N];

void add_edge(Edge **head, int u, int v) {
	head[u] = new (head[u], u, v) Edge;
}

int dfn[N];
int low[N];
int scc_no[N];
vector<int> scc[N];
int dt, sc;
int stk[N], tp;

void dfs(int u) {
	dfn[u] = low[u] = ++dt;
	stk[++tp] = u;
	for (Edge *e = head[u]; e; e = e->next) {
		int v = e->v;
		if (!dfn[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else
		if (!scc_no[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (low[u] == dfn[u]) {
		scc[++sc].clear();
		while (true) {
			int v = stk[tp--];
			scc_no[v] = sc;
			scc[sc].push_back(v);
			if (u == v) {
				break;
			}
		}
	}
}

int f[N];

int dp(int u) {
	if (f[u] != -1) {
		return f[u];
	}
	f[u] = scc[u].size();
	int t = 0;
	for (Edge *e = thead[u]; e; e = e->next) {
		int v = e->v;
		t = max(t, dp(v));
	}
	f[u] += t;
	return f[u];
}
	
int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, m;
		scanf("%d %d", &n, &m);
		memset(head, 0x0, sizeof head);
		for (int i = 1; i <= m; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			add_edge(head, u, v);
		}
		memset(dfn, 0, sizeof dfn);
		memset(scc_no, 0, sizeof scc_no);
		dt = sc = tp = 0;
		for (int i = 1; i <= n; i++) {
			if (!dfn[i]) {
				dfs(i);
			}
		}
		memset(thead, 0x0, sizeof thead);
		for (int u = 1; u <= n; u++) {
			for (Edge *e = head[u]; e; e = e->next) {
				int v = e->v;
				if (scc_no[u] != scc_no[v]) {
					add_edge(thead, scc_no[u], scc_no[v]);
				}
			}
		}
		int ans = 0;
		memset(f, -1, sizeof f);
		for (int i = 1; i <= sc; i++) {
			ans = max(ans, dp(i));
		}
		printf("%d\n", ans);
	}
	return 0;
}