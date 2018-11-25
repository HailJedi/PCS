#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 5e4+5;
const ll INF = 1e18;

struct Edge {
	Edge *next;
	int t, v;
	void *operator new(size_t, Edge *next, int t, int v) {
		static Edge pool[N*200], *p = pool;
		Edge *ret = p++;
		ret->next = next;
		ret->t = t;
		ret->v = v;
		return ret;
	}
} *head[N];

void add_edge(int u, int v, int t) {
	head[u] = new (head[u], t, v) Edge;
}

ll frq[N], dep[N], sz[N];
ll f[N];

void dfs(int u, int fa) {
	sz[u] = frq[u];
	for (Edge *e = head[u]; e; e = e->next) {
		if (e->v != fa) {
			dep[e->v] = dep[u] + e->t;
			dfs(e->v, u);
			sz[u] += sz[e->v];
		}
	}
}

void dfs2(int u, int fa) {
	for (Edge *e = head[u]; e; e = e->next) {
		if (e->v != fa) {
			f[e->v] = f[u] + (sz[1] - 2 * sz[e->v]) * e->t;
			dfs2(e->v, u);
		}
	}
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);

	int T, n, m;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		memset(head, 0x0, sizeof head);
		for (int i = 1; i < n; i++) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			w *= 2;
			add_edge(u, v, w);
			add_edge(v, u, w);
		}
		scanf("%d", &m);
		memset(frq, 0, sizeof frq);
		for (int i = 1; i <= m; i++) {
			int a, f;
			scanf("%d %d", &a, &f);
			frq[a] = f;
		}
		dfs(1, 0);
		f[1] = 0;
		for (int i = 1; i <= n; i++) {
			f[1] += frq[i] * dep[i];
		}
		dfs2(1, 0);
		ll ans = *min_element(f+1, f+1+n);
		printf("%lld\n", ans);
		bool ok = false;
		for (int i = 1; i <= n; i++) {
			if (f[i] == ans) {
				if (ok) {
					printf(" ");
				}
				printf("%d", i);
				ok = true;
			}
		}
		printf("\n");
	}
	return 0;
}