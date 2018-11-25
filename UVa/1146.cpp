#include <bits/stdc++.h>

using namespace std;

const int N = 2000 + 5;

struct Edge {
	Edge *next;
	int u, v;
	void *operator new(size_t, Edge *next, int u, int v) {
		static Edge pool[N*N*2], *p = pool;
		if (p == pool + N*N*2) {
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
	int s[N*2], tp;

	void add_edge(int x, int y) {
		head[x] = new (head[x], x, y) Edge;
	}
	
	bool dfs(int x) {
		if (mark[x^1]) {
			return false;
		}
		if (mark[x]) {
			return true;
		}
		mark[x] = true;
		s[++tp] = x;
		for (Edge *e = head[x]; e; e = e->next) {
			if (!dfs(e->v)) {
				return false;
			}
		}
		return true;
	}
	
	void init(int n) {
		this->n = n;
		memset(head, 0x0, sizeof head);
		memset(mark, 0, sizeof mark);
	}
	
	void add_clause(int x, int xv, int y, int yv) {
		x = x * 2 + xv;
		y = y * 2 + yv;
		add_edge(x^1, y);
		add_edge(y^1, x);
	}

	bool solve() {
		for (int i = 2; i <= 2 * n + 1; i += 2) {
			if (!mark[i] && !mark[i^1]) {
				tp = 0;
				if (!dfs(i)) {
					while (tp) {
						mark[s[tp--]] = false;
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

int t[N][2];
int n;

bool check(int dif) {
	solver.init(n);
	for (int i = 1; i <= n; i++) {
		for (int a = 0; a < 2; a++) {
			for (int j = i+1; j <= n; j++) {
				for (int b = 0; b < 2; b++) {
					if (abs(t[i][a] - t[j][b]) < dif) {
						solver.add_clause(i, a^1, j, b^1);
					}
				}
			}
		}
	}
	return solver.solve();
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	while (scanf("%d", &n) == 1) {
		int l = 0, r = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &t[i][0], &t[i][1]);
			r = max(r, t[i][1]);
		}
		while (l < r) {
			int m = (l+r+1) / 2;
			if (check(m)) {
				l = m;
			} else {
				r = m - 1;
			}
		}
		printf("%d\n", l);
	}
	return 0;
}