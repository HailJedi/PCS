/*
Created 2018-11-23
Luogu P3381
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 5000 + 5;
const int M = 50000 + 5;
const int INF = 0x3f3f3f3f;

struct Edge {
	Edge *next, *rev;
	int v, cap, cost;
	void *operator new(size_t, Edge *next, int v, int cap, int cost) {
		static Edge pool[M*2], *p = pool;
		Edge *ret = p++;
		ret->next = next;
		ret->v = v;
		ret->cap = cap;
		ret->cost = cost;
		return ret;
	}
} *head[N], *pre[N];

void add_edge(int u, int v, int cap, int cost) {
	head[u] = new (head[u], v, cap, cost) Edge;
	head[v] = new (head[v], u, 0, -cost) Edge;
	head[u]->rev = head[v];
	head[v]->rev = head[u];
}

int n, m, s, t;

int dis[N], curf[N];

struct Status {
	int d, u;
	Status(int d, int u) : d(d), u(u) {}
	bool operator < (const Status &st) const {
		return d > st.d;
	}
};

bool solve(int &mincost, int &maxflow) {
	memset(dis, INF, sizeof dis);
	pre[s] = 0x0;
	dis[s] = 0;
	curf[s] = INF;
	priority_queue<Status> q;
	q.push(Status(0, s));
	while (!q.empty()) {
		Status st = q.top();
		q.pop();
		int d = st.d, u = st.u;
		if (d > dis[u]) {
			continue;
		}
		if (u == t) {
			break;
		}
		for (Edge *e = head[u]; e; e = e->next) {
			if (e->cap > 0 && dis[e->v] > dis[u] + e->cost) {
				dis[e->v] = dis[u] + e->cost;
				pre[e->v] = e;
				curf[e->v] = min(curf[u], e->cap);
				q.push(Status(dis[e->v], e->v));
			}
		}
	}
	if (dis[t] == INF) {
		return false;
	}
	mincost += curf[t] * dis[t];
	maxflow += curf[t];
	int u = t;
	while (u != s) {
		Edge *&e = pre[u];
		e->cap -= curf[t];
		e->rev->cap += curf[t];
		u = e->rev->v;
	}
	return true;
}

int main() {
	scanf("%d %d %d %d", &n, &m, &s, &t);
	for (int i = 1; i <= m; i++) {
		int u, v, cap, cost;
		scanf("%d %d %d %d", &u, &v, &cap, &cost);
		add_edge(u, v, cap, cost);
		assert(cost >= 0);
	}
	int mincost = 0, maxflow = 0;
	while (solve(mincost, maxflow));
	printf("%d %d\n", maxflow, mincost);
	return 0;
}
