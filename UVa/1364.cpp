#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
const int M = 1000000 + 5;

struct Edge {
	Edge *next;
	int u, v;
	void *operator new(size_t, Edge *next, int u, int v) {
		static Edge pool[M*10], *p = pool;
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

bool del[N][N];
int col[N];
int dfn[N];
int low[N];
int dt;
stack<Edge*> stk;
int bc;
vector<int> bcc[N];
int bcol[N];
int odd[N];

void dfs(int u, int f) {
	dfn[u] = low[u] = ++dt;
	for (Edge *e = head[u]; e; e = e->next) {
		if (!dfn[e->v]) {
			stk.push(e);
			dfs(e->v, u);
			low[u] = min(low[u], low[e->v]);
			if (low[e->v] >= dfn[u]) {
				bcc[++bc].clear();
				while (true) {
					Edge *x = stk.top();
					stk.pop();
					if (bcol[x->u] != bc) {
						bcc[bc].push_back(x->u);
						bcol[x->u] = bc;
					}
					if (bcol[x->v] != bc) {
						bcc[bc].push_back(x->v);
						bcol[x->v] = bc;
					}
					if (x->u == u && x->v == e->v) {
						break;
					}
				}
			}
		} else 
		if (dfn[e->v] < dfn[u] && e->v != f) {
			stk.push(e);
			low[u] = min(low[u], dfn[e->v]);
		}
	}
}

bool bipartie(int u) {
	for (Edge *e = head[u]; e; e = e->next) {
		if (bcol[e->v] == bcol[u]) {
			if (col[e->v] == col[u]) {
				return false;
			}
			if (col[e->v] == -1) {
				col[e->v] = col[u] ^ 1;
				if (!bipartie(e->v)) {
					return false;
				}
			}
		}
	}
	return true;
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int n, m;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		memset(del, false, sizeof del);
		for (int i = 1; i <= m; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			del[u][v] = del[v][u] = true;
		}
		memset(head, 0x0, sizeof head);
		for (int i = 1; i <= n; i++) {
			for (int j = i+1; j <= n; j++) {
				if (!del[i][j]) {
					add_edge(i, j);
					add_edge(j, i);
				}
			}
		}
		bc = 0;
		dt = 0;
		memset(dfn, 0, sizeof dfn);
		memset(bcol, 0, sizeof bcol);
		for (int i = 1; i <= n; i++) {
			if (!dfn[i]) {
				dfs(i, -1);
			}
		}
		memset(odd, 0, sizeof odd);
		for (int i = 1; i <= bc; i++) {
			for (int j = 0; j < bcc[i].size(); j++) {
				bcol[bcc[i][j]] = i;
			}
			memset(col, -1, sizeof col);
			int u = bcc[i][0];
			col[u] = 0;
			if (!bipartie(u)) {
				for (int j = 0; j < bcc[i].size(); j++) {
					odd[bcc[i][j]] = 1;
				}
			}
		}
		int ans = n;
		for (int i = 1; i <= n; i++) {
			ans -= odd[i];
		}
		printf("%d\n", ans);
	}
	return 0;
}