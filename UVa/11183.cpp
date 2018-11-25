#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
const int M = 40000 + 5;
const int INF = 0x3f3f3f3f;

struct Edge {
	int u, v, w;
	void *operator new(size_t, int u, int v, int w) {
		static Edge pool[M], *p = pool;
		if (p == pool + M) {
			p = pool;
		}
		Edge *ret = p++;
		ret->u = u;
		ret->v = v;
		ret->w = w;
		return ret;
	}
} *edge[M];

int n, m;
int inw[N], pre[N], sc[N], id[N];

int Zhu_Liu() {
	int ret = 0, root = 0;
	while (true) {
		memset(inw, INF, sizeof inw);
		memset(pre, -1, sizeof pre);
		memset(sc, -1, sizeof sc);
		memset(id, -1, sizeof id);
		for (int i = 0; i < m; i++) {
			if (edge[i]->w < inw[edge[i]->v] && edge[i]->u != edge[i]->v) {
				inw[edge[i]->v] = edge[i]->w;
				pre[edge[i]->v] = edge[i]->u;
			}
		}
		pre[root] = 0;
		inw[root] = 0;
		for (int i = 0; i < n; i++) {
			if (inw[i] == INF) {
				return -1;
			}
			ret += inw[i];
		}
		int idx = 0;
		for (int i = 0; i < n; i++) {
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
			return ret;
		}
		for (int i = 0; i < n; i++) {
			if (id[i] == -1) {
				id[i] = idx++;
			}
		}
		for (int i = 0; i < m; i++) {
			edge[i]->w -= inw[edge[i]->v];
			edge[i]->u = id[edge[i]->u];
			edge[i]->v = id[edge[i]->v];
		}
		n = idx;
		root = id[root];
	}
	return -1;
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int T, kase = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < m; i++) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			edge[i] = new (u, v, w) Edge;
		}
		printf("Case #%d: ", ++kase);
		int ans = Zhu_Liu();
		if (ans != -1) {
			printf("%d\n", ans);
		} else {
			printf("Possums!\n");
		}
	}
	return 0;
}