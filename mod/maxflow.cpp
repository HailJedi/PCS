/*
Created 2018-11-23
Luogu P3376
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 10000 + 5;
const int M = 100000 + 5;
const int INF = 0x3f3f3f3f;

struct Edge {
	Edge *next, *rev;
	int v, cap;
	void *operator new(size_t, Edge *next, int v, int cap) {
		static Edge pool[M*2], *p = pool;
		Edge *ret = p++;
		ret->next = next;
		ret->v = v;
		ret->cap = cap;
		return ret;
	}
} *head[N], *cur[N];

void add_edge(int u, int v, int c) {
	head[u] = new (head[u], v, c) Edge;
	head[v] = new (head[v], u, 0) Edge;
	head[u]->rev = head[v];
	head[v]->rev = head[u];
}

int n, m, s, t;
int level[N];

bool bfs() {
	memset(level, -1, sizeof level);
	level[s] = 0;
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (Edge *e = head[u]; e; e = e->next) {
			if (e->cap > 0 && level[e->v] == -1) {
				level[e->v] = level[u] + 1;
				q.push(e->v);
			}
		}
	}
	return level[t] != -1;
}

int dfs(int u, int f) {
	if (u == t || f == 0) {
		return f;
	}
	int vf = 0;
	for (Edge *e = cur[u]; e && f; e = e->next, cur[u] = e) {
		int v = e->v;
		if (e->cap > 0 && level[u] + 1 == level[v]) {
			int fl = dfs(v, min(e->cap, f));
			f -= fl;
			e->cap -= fl;
			e->rev->cap += fl;
			vf += fl;
		}
	}
	return vf;
}

int main() {
	scanf("%d %d %d %d", &n, &m, &s, &t);
	for (int i = 1; i <= m; i++) {
		int u, v, c;
		scanf("%d %d %d", &u, &v, &c);
		add_edge(u, v, c);
	}
	int maxf = 0;
	while (bfs()) {
		for (int i = 1; i <= n; i++) {
			cur[i] = head[i];
		}
		while (int flow = dfs(s, INF)) {
			maxf += flow;
		}
	}
	printf("%d\n", maxf);
	return 0;
}
