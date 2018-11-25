#include <bits/stdc++.h>

using namespace std;

const int N = 60 + 5;
const int M = 10000 + 5;
const int maxC = 1e9;
const int LG = 31;
const int INF = 0x3f3f3f3f;

struct Edge {
	int u, v, b, c;
	void *operator new(size_t, int u, int v, int b, int c) {
		static Edge pool[LG*M], *p = pool;
		if (p == pool + LG*M) {
			p = pool;
		}
		Edge *ret = p++;
		ret->u = u;
		ret->v = v;
		ret->b = b;
		ret->c = c;
		return ret;
	}
} *edge[M], *eg[M];

int n, m, C;
int inw[N], pre[N], id[N], sc[N];

bool Zhu_Liu(int lim) {
	int pt = 0;
	for (int i = 0; i < m; i++) {
		if (edge[i]->b >= lim) {
			eg[pt++] = new (edge[i]->u, edge[i]->v, edge[i]->b, edge[i]->c) Edge;
		}
	}
	int root = 0, mn = 0, nd = n;
	while (true) {
		memset(inw, INF, sizeof inw);
		memset(pre, -1, sizeof pre);
		memset(id, -1, sizeof id);
		memset(sc, -1, sizeof sc);
		for (int i = 0; i < pt; i++) {
			if (eg[i]->c < inw[eg[i]->v] && eg[i]->u != eg[i]->v) {
				inw[eg[i]->v] = eg[i]->c;
				pre[eg[i]->v] = eg[i]->u;
			}
		}
		pre[root] = root;
		inw[root] = 0;
		for (int i = 0; i < nd; i++) {
			if (inw[i] == INF) {
				return false;
			}
			mn += inw[i];
		}
		int idx = 0;
		for (int i = 0; i < nd; i++) {
			if (sc[i] == -1) {
				int u = i;
				while (sc[u] == -1) {
					sc[u] = i;
					u = pre[u];
				}
				if (sc[u] == i && u != root) {
					for (int v = u, f = 1; v != u || f; v = pre[v], f = 0) {
						id[v] = idx;
					}
					idx++;
				}
			}
		}
		if (idx == 0) {
			return mn <= C;
		}
		for (int i = 0; i < nd; i++) {
			if (id[i] == -1) {
				id[i] = idx++;
			}
		}
		for (int i = 0; i < pt; i++) {
			eg[i]->c -= inw[eg[i]->v];
			eg[i]->u = id[eg[i]->u];
			eg[i]->v = id[eg[i]->v];
		}
		nd = idx;
		root = id[root];
	}
	return false;
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &n, &m, &C);
		for (int i = 0; i < m; i++) {
			int u, v, b, c;
			scanf("%d %d %d %d", &u, &v, &b, &c);
			edge[i] = new (u, v, b, c) Edge;
		}
		int l = 0, r = 1e6+5;
		while (r - l > 1) {
			int mid = (l + r) / 2;
			if (Zhu_Liu(mid)) {
				l = mid;
			} else {
				r = mid;
			}
		}
		if (l == 0) {
			printf("streaming not possible.\n");
		} else {
			printf("%d kbps\n", l);
		}
	}
	return 0;
}