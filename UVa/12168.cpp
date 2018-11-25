#include <bits/stdc++.h>

using namespace std;

const int N = 500 + 5;
const int M = N * N;

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

int V;
bool vis[N];
int Left[N];

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
	for (int i = 1; i <= V; i++) {
		memset(vis, false, sizeof vis);
		ret += match(i);
	}
	return ret;
}

char love_type[N], hate_type[N];
int love_obj[N], hate_obj[N];

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	int T;
	scanf("%d", &T);
	while (T--) {
		int t;
		scanf("%d %d %d", &t, &t, &V);
		for (int i = 1; i <= V; i++) {
			char A[10], B[10];
			scanf("%s %s", A, B);
			love_type[i] = A[0];
			hate_type[i] = B[0];
			sscanf(A+1, "%d", &love_obj[i]);
			sscanf(B+1, "%d", &hate_obj[i]);
		}
		memset(head, 0x0, sizeof head);
		for (int i = 1; i <= V; i++) {
			if (love_type[i] == 'C') {
				for (int j = 1; j <= V; j++) {
					if (love_type[j] == 'D') {
						if (love_obj[i] == hate_obj[j] || hate_obj[i] == love_obj[j]) {
							add_edge(i, j);
						}
					}
				}
			}
		}
		printf("%d\n", V - KM());
	}
	return 0;
}
