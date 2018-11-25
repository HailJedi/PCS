#include <bits/stdc++.h>

using namespace std;

const int N = 300 + 5;

struct Edge {
	Edge *next;
	int u, v;
	void *operator new(size_t, Edge *next, int u, int v) {
		static Edge pool[N*10], *p = pool;
		if (p == pool + N*10) {
			p = pool;
		}
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

int col[N];

bool bipartie(int u) {
	for (Edge *e = head[u]; e; e = e->next) {
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
	return true;
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int n;
	while (scanf("%d", &n) == 1 && n) {
		int u, v;
		memset(head, 0x0, sizeof head);
		while (scanf("%d %d", &u, &v) == 2 && u && v) {
			add_edge(u, v);
			add_edge(v, u);
		}
		memset(col, -1, sizeof col);
		col[1] = 0;
		if (bipartie(1)) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	return 0;
}