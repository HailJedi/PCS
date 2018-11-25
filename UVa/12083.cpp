#include <bits/stdc++.h>

using namespace std;

const int N = 500 + 5;
const int L = 100 + 5;
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

char s[N];
int h[N];
char sp[N][L], m[N][L];

bool S[N], T[N];
int Left[N];

int match(int u) {
	S[u] = true;
	for (Edge *e = head[u]; e; e = e->next) {
		if (!T[e->v]) {
			T[e->v] = true;
			if (!Left[e->v] || match(Left[e->v])) {
				Left[e->v] = u;
				return 1;
			}
		}
	}
	return 0;
}

int n;

int KM() {
	int ret = 0;
	memset(Left, 0, sizeof Left);
	for (int i = 1; i <= n; i++) {
		memset(S, false, sizeof S);
		memset(T, false, sizeof T);
		ret += match(i);
	}
	return ret;
}	

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d %c %s %s", &h[i], &s[i], &m[i], &sp[i]);
		}
		memset(head, 0x0, sizeof head);
		for (int i = 1; i <= n; i++) if (s[i] == 'M') {
			for (int j = 1; j <= n; j++) if (s[j] == 'F') {
				if (abs(h[i]-h[j]) <= 40 && strcmp(m[i], m[j]) == 0 && strcmp(sp[i], sp[j]) != 0) {
					add_edge(i, j);
				}
			}
		}
		printf("%d\n", n - KM());
	}
	return 0;
}
