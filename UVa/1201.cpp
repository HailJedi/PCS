#include <bits/stdc++.h>

using namespace std;

const int N = 500 + 5;
const int M = N*N;

struct Edge {
	Edge *next;
	int v;
	void *operator new(size_t, Edge *next, int v) {
		static Edge pool[M], *p = pool;
		if (p == pool + M) {
			p = pool;
		}
		Edge *ret = p++;
		ret->next = next;
		ret->v = v;
		return ret;
	}
} *head[N];

void add_edge(int u, int v) {
	head[u] = new (head[u], v) Edge;
}

int n;
bool vis[2*N];
int Left[2*N];

int match(int u) {
	vis[u] = true;
	for (Edge *e = head[u]; e; e = e->next) {
		if (!vis[e->v]) {
			vis[e->v] = true;
			if (!Left[e->v] || match(Left[e->v])) {
				Left[e->v] = u;
				return 1;
			}
		}
	}
	return 0;
}

int KM() {
	int ret = 0;
	memset(Left, 0, sizeof Left);
	for (int i = 1; i <= n; i++) {
		memset(vis, false, sizeof vis);
		ret += match(i);
	}
	return ret;
}

int sche[N];
int sr[N], sc[N];
int er[N], ec[N];

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			int h, m;
			scanf("%d:%d", &h, &m);
			sche[i] = h * 60 + m;
			scanf("%d %d %d %d", &sr[i], &sc[i], &er[i], &ec[i]);
		}
		memset(head, 0x0, sizeof head);
		for (int i = 1; i <= n; i++) {
			for (int j = i+1; j <= n; j++) {
				int fin = sche[i] + abs(sr[i]-er[i]) + abs(sc[i]-ec[i]);
				if (fin + abs(er[i]-sr[j]) + abs(ec[i]-sc[j]) <= sche[j] - 1) {
					add_edge(i, j+n); 
				}
			}
		}
		printf("%d\n", n - KM());
	}
	return 0;
}
