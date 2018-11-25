#include <bits/stdc++.h>

using namespace std;

const int N = 50000 + 5;

struct Edge {
	Edge *next;
	int u, v;
	void *operator new(size_t, Edge *next, int u, int v) {
		static Edge pool[N*100], *p = pool;
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

int dfn[N];
int low[N];
bool is_cut[N];
int bcol[N];
stack<Edge*> stk;
vector<int> bcc[N];
int dt, bc;

void dfs(int u, int f) {
	dfn[u] = low[u] = ++dt;
	int son = 0;
	for (Edge *e = head[u]; e; e = e->next) {
		int v = e->v;
		if (!dfn[v]) {
			son++;
			stk.push(e);
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u]) {
				is_cut[u] = true;
				bcc[++bc].clear();
				while (true) {
					Edge *x = stk.top();
					stk.pop();
					if (bcol[x->v] != bc) {
						bcc[bc].push_back(x->v);
						bcol[x->v] = bc;
					}
					if (bcol[x->u] != bc) {
						bcc[bc].push_back(x->u);
						bcol[x->u] = bc;
					}
					if (x->v == v && x->u == u) {
						break;
					}
				}
			}
		} else 
		if (dfn[v] < dfn[u] && v != f) {
			stk.push(e);
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (f == -1 && son == 1) {
		is_cut[u] = false;
	}
}

int main() {
//	freopen("read", "r", stdin);	
//	freopen("write", "w", stdout);
	
	int n, m, kase = 0;
	while (scanf("%d", &m) == 1 && m) {
		memset(head, 0x0, sizeof head);
		n = 0;
		for (int i = 1; i <= m; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			add_edge(u, v);
			add_edge(v, u);
			n = max(n, u);
			n = max(n, v);
		}
		memset(dfn, 0, sizeof dfn);
		memset(is_cut, false, sizeof is_cut);
		memset(bcol, 0, sizeof bcol);
		dt = bc = 0;
		for (int i = 1; i <= n; i++) {
			if (!dfn[i]) {
				dfs(i, -1);
			}
		}
		int ans = 0;
		long long way = 1;
		for (int i = 1; i <= bc; i++) {
			int cut_cnt = 0;
			for (int j = 0; j < bcc[i].size(); j++) {
				cut_cnt += is_cut[bcc[i][j]];
			}
			if (cut_cnt == 1) {
				ans++;
				way *= (bcc[i].size() - 1);
			}
		}
		if (bc == 1) {
			ans = 2;
			way = bcc[1].size() * (bcc[1].size()-1) / 2;
		}
		printf("Case %d: %d %lld\n", ++kase, ans, way);
	}
	return 0;
}