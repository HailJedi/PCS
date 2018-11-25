#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const int M = 100000 + 5;

struct Edge {
	Edge *next;
	int u, v;
	void *operator new(size_t, Edge *next, int u, int v) {
		static Edge pool[M*4], *p = pool;
		if (p == pool + M*4) {
			p = pool;
		}
		Edge *ret = p++;
		ret->next = next;
		ret->u = u;
		ret->v = v;
		return ret;
	}
};

struct TwoSAT {
	int n;
	Edge *head[N*2];
	bool mark[N*2];
	int stk[N*2], tp;

	void add_edge(int x, int y) {
		head[x] = new (head[x], x, y) Edge;
	}
	
	void init(int n) {
		this->n = n;
		memset(mark, 0, sizeof mark);
		memset(head, 0x0, sizeof head);
	}
	
	void add_clause(int x, int xv, int y, int yv) {
		x = x * 2 + xv;
		y = y * 2 + yv;
		add_edge(x^1, y);
		add_edge(y^1, x);
	}
	
	bool dfs(int x) {
		if (mark[x^1]) {
			return false;
		}
		if (mark[x]) {
			return true;
		}
		mark[x] = true;
		stk[++tp] = x;
		for (Edge *e = head[x]; e; e = e->next) {
			if (!dfs(e->v)) {
				return false;
			}
		}
		return true;
	}
	
	bool solve() {
		for (int i = 2; i <= 2*n+1; i += 2) {
			if (!mark[i] && !mark[i^1]) {
				tp = 0;
				if (!dfs(i)) {
					while (tp) {
						mark[stk[tp--]] = false;
					}
					if (!dfs(i^1)) {
						return false;
					}
				}
			}
		}
		return true;
	}
} solver;

int age[N];
int ave;
int n, m;

bool is_young(int x) {
	return age[x] * n < ave;
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	while (scanf("%d %d", &n, &m) == 2 && n) {
		ave = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &age[i]);
			ave += age[i];
		}
		solver.init(n);
		for (int i = 1; i <= m; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			if (u == v) {
				continue;
			}
			if (is_young(u) == is_young(v)) {
				solver.add_clause(u, 0, v, 0);
				solver.add_clause(u, 1, v, 1);
			} else {
				solver.add_clause(u, 1, v, 1);
			}
		}
		if (!solver.solve()) {
			printf("No solution\n");
		} else {
			for (int i = 1; i <= n; i++) {
				printf("%c\n", solver.mark[i*2] ? 'C' : is_young(i) ? 'B' : 'A');
			}
		}
	}
	return 0;
}
		