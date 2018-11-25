#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
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

bool S[N], T[N];
bool mark[N];
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

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	int R, C, n;
	while (scanf("%d %d %d", &R, &C, &n) == 3 && R) {
		memset(head, 0x0, sizeof head);
		for (int i = 1; i <= n; i++) {
			int r, c;
			scanf("%d %d", &r, &c);
			add_edge(r, c);
		}
		int sum = 0;
		memset(Left, 0, sizeof Left);
		for (int i = 1; i <= R; i++) {
			memset(S, false, sizeof S);
			memset(T, false, sizeof T);
			sum += match(i);
		}
		memset(mark, false, sizeof mark);
		for (int i = 1; i <= C; i++) {
			mark[Left[i]] = true;
		}
		memset(S, false, sizeof S);
		memset(T, false, sizeof T);
		for (int i = 1; i <= R; i++) {
			if (!mark[i]) {
				match(i);
			}
		}
		printf("%d", sum);
		for (int i = 1; i <= R; i++) {
			if (!S[i]) {
				printf(" r%d", i);
			}
		}
		for (int i = 1; i <= C; i++) {
			if (T[i]) {
				printf(" c%d", i);
			}
		}
		puts("");
	}
	return 0;
}
