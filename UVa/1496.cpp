#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 5;
const int K = 10;
const int M = 1000 + 5;
const int INF = 0x3f3f3f3f;

struct Edge {
	Edge *next;
	int v, w;
	void *operator new(size_t, Edge *next, int v, int w) {
		static Edge pool[M*1000], *p = pool;
		Edge *ret = p++;
		ret->next = next;
		ret->v = v;
		ret->w = w;
		return ret;
	}
} *head[N];

void add_edge(int u, int v, int w) {
	head[u] = new (head[u], v, w) Edge;
}

int n, m, k;
int dis[N][1<<K];
bool vis[N];
bool ok[1<<K];
int ans[1<<K];

int trans(int x) {
	if (x <= k) {
		return x-1;
	}
	if (x > n-k) {
		return x-n+2*k-1;
	}
	return x+k-1;
}

bool check(int s) {
	int sum = 0;
	for (int i = 0; i < k; i++) {
		sum += ((s>>i) & 1);
		sum -= ((s>>(i+k)) & 1);
	}
	return sum == 0;
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);

	int T;
	scanf("%d", &T);
	while (T--) {
		memset(head, 0x0, sizeof head);
		scanf("%d %d %d", &n, &m, &k);
		for (int i = 1; i <= m; i++) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			u = trans(u);
			v = trans(v);
			add_edge(u, v, w);
			add_edge(v, u, w);
		}
		memset(dis, INF, sizeof dis);
		for (int i = 0; i < 2*k; i++) {
			dis[i][1<<i] = 0;
		}
		int all = 1<<(2*k);
		for (int i = 0; i < all; i++) {
			queue<int> q;
			for (int j = 0; j < n; j++) {
				for (int k = i; k; k = (k-1) & i) {
					dis[j][i] = min(dis[j][i], dis[j][i^k] + dis[j][k]);
				}
				if (dis[j][i] != INF) {
					q.push(j);
					vis[j] = true;
				}
			}
			while (!q.empty()) {
				int u = q.front();
				q.pop();
				vis[u] = false;
				for (Edge *e = head[u]; e; e = e->next) {
					if (dis[e->v][i] > dis[u][i] + e->w) {
						dis[e->v][i] = dis[u][i] + e->w;
						if (!vis[e->v]) {
							q.push(e->v);
							vis[e->v] = true;
						}
					}
				}
			}
			ok[i] = check(i);
			ans[i] = INF;
			for (int j = 0; j < n; j++) {
				ans[i] = min(ans[i], dis[j][i]);
			}
			for (int j = i; j; j = (j-1) & i) if (ok[j]) {
				ans[i] = min(ans[i], ans[i^j] + ans[j]);
			}
		}
		if (ans[all-1] == INF) {
			printf("No solution\n");
		} else {
			printf("%d\n", ans[all-1]);
		}
	}
	return 0;
}