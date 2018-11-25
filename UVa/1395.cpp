#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;
const int M = N * N;

struct Edge {
	int u, v, w;
	Edge() {}
	Edge(int u, int v, int w) : u(u), v(v), w(w) {}
	bool operator < (const Edge &e) const {
		return w < e.w;
	}
} edge[M];

int fa[N], rk[N];

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void unite(int x, int y) {
	if (rk[x] < rk[y]) {
		fa[x] = y;
		rk[y] += rk[x];
	} else {
		fa[y] = x;
		rk[x] += rk[y];
	}
}

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	int n, m;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		for (int i = 1; i <= m; i++) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			edge[i] = Edge(u, v, w);
		}
		sort(edge+1, edge+1+m);
		int ans = 1e9;
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				fa[j] = j;
				rk[j] = 1;
			}
			int cnt = 0;
			for (int j = i; j <= m; j++) {
				int u = find(edge[j].u), v = find(edge[j].v);
				if (u != v) {
					unite(u, v);
					cnt++;
					if (cnt == n-1) {
						ans = min(ans, edge[j].w - edge[i].w);
						break;
					}
				}
			}
			if (cnt < n-1) {
				break;
			}
		}
		printf("%d\n", ans == 1e9 ? -1 : ans);
	}
	return 0;
}
