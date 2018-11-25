#include <bits/stdc++.h>

using namespace std;

const int N = 20000 + 5;
const int M = 50000 + 5;

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
} *head[N];

void add_edge(int u, int v) {
	head[u] = new (head[u], u, v) Edge;
}

vector<int> scc[N];
int dt, sc;
int dfn[N];
int low[N];
int stk[N], tp;
int in[N], out[N];
int scc_no[N];

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
		sc++;
		while (true) {
			int v = stk[tp--];
			scc_no[v] = sc;
			if (v == u) {
				break;
			}
		}
	}
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
			add_edge(u, v);
		}
		memset(scc_no, 0, sizeof scc_no);
		memset(dfn, 0, sizeof dfn);
		dt = sc = tp = 0;
		for (int i = 1; i <= n; i++) {
			if (!dfn[i]) {
				dfs(i);
			}
		}
		int ans = 0;
		for (int i = 1; i <= sc; i++) {
			in[i] = out[i] = 1;
		}
		for (int u = 1; u <= n; u++) {
			for (Edge *e = head[u]; e; e = e->next) {
				if (scc_no[u] != scc_no[e->v]) {
					out[scc_no[u]] = in[scc_no[e->v]] = 0;
				}
			}
		}
		int a = 0, b = 0;
		for (int i = 1; i <= sc; i++) {
			a += in[i];
			b += out[i];
		}
		ans = max(a, b);
		if (sc == 1) {
			ans = 0;
		}
		printf("%d\n", ans);
	}
	return 0;
}