#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;
const int INF = 1e9;

int f[N];
int h[N];
int L, R;

struct Edge {
	Edge *next;
	int v, c;
	void *operator new(size_t, Edge *next, int v, int c) {
		static Edge pool[N*20], *p = pool;
		Edge *ret = p++;
		ret->next = next;
		ret->v = v;
		ret->c = c;
		return ret;
	}
} *head[N];

void add_edge(int u, int v, int c) {
	head[u] = new (head[u], v, c) Edge;
}

void dfs(int u) {
	for (Edge *e = head[u]; e; e = e->next) {
		h[e->v] = h[u] + e->c;
		dfs(e->v);
	}
}

void dp(int u, bool bob) {
	if (f[u] != -1) {
		return;
	}
	f[u] = bob ? -INF : INF;
	if (head[u] == 0x0) {
		if (L <= h[u] && h[u] <= R) {
			f[u] = f[u] = 0;
		}
		return;
	}
	for (Edge *e = head[u]; e; e = e->next) {
		dp(e->v, !bob);
		if (L <= f[e->v] + e->c + h[u] && f[e->v] + e->c + h[u] <= R) {
			if (bob) {
				f[u] = max(f[u], f[e->v] + e->c);
			} else {
				f[u] = min(f[u], f[e->v] + e->c);
			}
		}
	}
}
	
int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int n;
	while (scanf("%d %d %d", &n, &L, &R) == 3) {
		memset(head, 0x0, sizeof head);
		for (int i = 1; i < n; i++) {
			int u, v, c;
			scanf("%d %d %d", &u, &v, &c);
			add_edge(u, v, c);
		}
		dfs(0);
		memset(f, -1, sizeof f);
		dp(0, 1);
		if (f[0] == -INF) {
			puts("Oh, my god!");
		} else {
			printf("%d\n", f[0]);
		}
	}
	return 0;
}
