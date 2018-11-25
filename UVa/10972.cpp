#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;

struct Edge {
	Edge *next;
	int u, v;
	bool is_brig;
	void *operator new(size_t, Edge *next, int u, int v) {
		static Edge pool[N*N*2], *p = pool;
		if (p == pool + N*N*2) {
			p = pool;
		}
		Edge *ret = p++;
		ret->next = next;
		ret->u = u;
		ret->v = v;
		ret->is_brig = false;
		return ret;
	}
} *head[N];

void add_edge(int u, int v) {
	head[u] = new (head[u], u, v) Edge;
}

int adj[N][N];
int dfn[N], low[N];
int bc_no[N];
int dt, bc;
int deg[N];
bool mark[N];

void dfs(int u, int f) {
	dfn[u] = low[u] = ++dt;
	for (Edge *e = head[u]; e; e = e->next) {
		int v = e->v;
		if (!dfn[v]) {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) {
				bc++;
			}
		} else 
		if (v != f) {
			low[u] = min(low[u], dfn[v]);
		}
	}
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		memset(head, 0x0, sizeof head);
		for (int i = 1; i <= m; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			add_edge(u, v);
			add_edge(v, u);
		}
		memset(dfn, 0, sizeof dfn);
		dt = bc = 0;
		for (int i = 1; i <= n; i++) {
			if (!dfn[i]) {
				dfs(i, -1);
				bc++;
			}
		}
		if (bc == 1) {
			printf("0\n");
			continue;
		}
		memset(mark, false, sizeof mark);
		memset(deg, 0, sizeof deg);
		for (int u = 1; u <= n; u++) {
			if (head[u] == 0x0) {
				mark[low[u]] = true;
				continue;
			}
			for (Edge *e = head[u]; e; e = e->next) {
				int v = e->v;
				mark[low[u]] = mark[low[v]] = true;
				if (low[u] != low[v]) {
					deg[low[u]]++;
				}
			}
		}
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			if (mark[i] && deg[i] == 0) {
				ans += 2;
			} else 
			if (deg[i] == 1) {
				ans++;
			}
		}
		printf("%d\n", (ans+1)/2);
		/*
 		memset(deg, 0, sizeof deg);
 		for (int u = 1; u <= n; u++) {
 			for (Edge *e = head[u]; e; e = e->next) {
 				int v = e->v;
 				if (bc_no[u] != bc_no[v]) {
 					deg[bc_no[u]]++;
 				}
 			}
 		}
 		int a = 0, b = 0;
 		for (int i = 1; i <= n; i++) {
 			if (head[i] == 0x0) {
 				a++;
 			}
 		}
 		for (int i = 1; i <= bc; i++) {
			if (deg[i] == 1) {
 				b++;
 			}
 		}
 		printf("%d\n", (b+1+2*a)/2);
 		*/
	}
	return 0;
}
