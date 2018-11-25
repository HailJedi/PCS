#include <bits/stdc++.h>

using namespace std;

const int N = 200 + 5;
const int M = N * N;
const int INF = 0x3f3f3f3f;

struct Edge {
	Edge *next;
	int v, w;
	void *operator new(size_t, Edge *next, int v, int w) {
		static Edge pool[M], *p = pool;
		if (p == pool + M) {
			p = pool;
		}
		Edge *ret = p++;
		ret->next = next;
		ret->v = v;
		ret->w = w;
		return ret;
	}
} *head[N];

void add_edge(int u, int v, int d) {
	head[u] = new (head[u], v, d) Edge;
}

int n;
int Left[N];
int Lx[N], Ly[N];
int mn[N];
bool vis[N];

bool match(int u) {
	vis[u] = true;
	for (Edge *e = head[u]; e; e = e->next) {
		if (!vis[e->v]) {
			int diff = Lx[u] + Ly[e->v] - e->w;
			if (diff == 0) {
				vis[e->v] = true;
				if (!Left[e->v] || match(Left[e->v])) {
					Left[e->v] = u;
					return true;
				}
			} else {
				mn[e->v] = min(mn[e->v], diff);
			}
		}
	}
	return false;
}

bool check(int u) {
	vis[u] = true;
	for (Edge *e = head[u]; e; e = e->next) {
		if (!vis[e->v]) {
			vis[e->v] = true;
			if (!Left[e->v] || check(Left[e->v])) {
				Left[e->v] = u;
				return true;
			}
		}
	}
	return false;
}

void update() {
	int a = INF;
	for (int i = n+1; i <= 2*n; i++) {
		if (!vis[i]) {
			a = min(a, mn[i]);
		}
	}
	for (int i = 1; i <= n; i++) {
		if (vis[i]) Lx[i] -= a;
		if (vis[i+n]) Ly[i+n] += a;
		else mn[i+n] -= a;
	}
}

int KM() {
	memset(Left, 0, sizeof Left);
	for (int i = 1; i <= n; i++) {
		memset(vis, false, sizeof vis);
		if (!check(i)) {
			return 233;
		}
	}
	memset(Lx, -INF, sizeof Lx);
	memset(Ly, 0, sizeof Ly);
	memset(Left, 0, sizeof Left);
	for (int i = 1; i <= n; i++) {
		for (Edge *e = head[i]; e; e = e->next) {
			Lx[i] = max(Lx[i], e->w);
		}
	}
	for (int i = 1; i <= n; i++) {
		memset(mn, INF, sizeof mn);
		while (true) {
			memset(vis, false, sizeof vis);
			if (match(i)) {
				break;
			} else {
				update();
			}
		}
	}
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		ret += Lx[i] + Ly[i+n];
	}
	return ret;
}

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	while (scanf("%d", &n) == 1 && n) {
		memset(head, 0x0, sizeof head);
		for (int i = 1; i <= n; i++) {
			int j, d;
			while (scanf("%d", &j) == 1 && j) {
				scanf("%d", &d);
				add_edge(i, j+n, -d);
			}
		}
		int ans = KM();
		if (ans == 233) {
			puts("N");
		} else {
			printf("%d\n", -ans);
		}
	}
	return 0;
}
