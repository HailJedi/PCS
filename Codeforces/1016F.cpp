/*
Created 2018-11-28
"Road Projects"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 300000 + 5;

vector<int> g[N];

struct Node {
	long long d[2];
	int id;
	bool operator < (const Node &nd) const {
		if (d[1] != nd.d[1]) {
			return d[1] > nd.d[1];
		}
		return id < nd.id;
	}
} node[N];

struct Edge {
	Edge *next;
	int v, w;
	void *operator new (size_t, Edge *next, int v, int w) {
		static Edge pool[3*N], *p = pool;
		Edge *ret = p++;
		ret->next = next;
		ret->v = v;
		ret->w = w;
		return ret;
	}
} *head[N];

void add_edge(int u, int v, int w) {
	head[u] = new (head[u], v, w) Edge;
	head[v] = new (head[v], u, w) Edge;
}

void dfs(int u, int fa, int b) {
	for (Edge *e = head[u]; e; e = e->next) {
		if (e->v != fa) {
			node[e->v].d[b] = node[u].d[b] + e->w;
			dfs(e->v, u, b);
		}
	}
}

bool cmp(Node &nd1, Node &nd2) {
	return nd1.d[0] - nd1.d[1] < nd2.d[0] - nd2.d[1];
}

int order[N];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i < n; i++) {	
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		add_edge(u, v, w);
	}
	for (int i = 1; i <= n; i++) {
		node[i].id = i;	
	}
	dfs(1, 0, 0);
	dfs(n, 0, 1);
	sort(node+1, node+1+n, cmp);
	for (int i = 1; i <= n; i++) {	
		order[node[i].id] = i;
	}
	set<Node> st;
	st.insert(node[n]);
	long long mx = 0;
	for (int i = n-1; i >= 1; i--) {
		int u = node[i].id;
		for (Edge *e = head[u]; e; e = e->next) {
			if (order[e->v] > order[u]) {
				st.erase(node[order[e->v]]);
			}
		}
		if (!st.empty()) {
			mx = max(mx, node[i].d[0] + (*st.begin()).d[1]);	
		}
		for (Edge *e = head[u]; e; e = e->next) {
			if (order[e->v] > order[u]) {
				st.insert(node[order[e->v]]);
			}
		}
		st.insert(node[i]);
	}
	while (m--) {
		long long x;
		scanf("%lld", &x);
		printf("%lld\n", min(node[order[n]].d[0], mx + x));
	}
	return 0;
}
