#include <bits/stdc++.h>

using namespace std;

const int N = 10000 + 5;
const int S = N * 4;

struct FourSAT {
	int n;
	bool mark[S], err[S];
	int stk[S], tp;
	vector<int> g[S];
	
	void add_edge(int u, int v) {
		g[u].push_back(v);
	}
	
	void init(int n) {
		this->n = n;
		for (int i = 0; i < 4*n; i++) {
			g[i].clear();
		}
		memset(mark, false, sizeof mark);
		memset(err, false, sizeof err);
	}

	void draw(int u) {
		if (err[u]) {
			return;
		}
		err[u] = true;
		for (int i = 0; i < g[u].size(); i++) {
			draw(g[u][i]);
		}
	}
	
	bool dfs(int u) {
		if (mark[u^1] || mark[u^2] || mark[u^3] || err[u]) {
			return false;
		}
		if (mark[u]) {
			return true;
		}
		mark[u] = true;
		stk[++tp] = u;
		for (int i = 0; i < g[u].size(); i++) {
			if (!dfs(g[u][i])) {
				return false;
			}
		}
		return true;
	}
	
	bool solve() {
		for (int i = 0; i < 4*n; i += 4) {
			if (!mark[i] && !mark[i^1] && !mark[i^2] && !mark[i^3]) {
				bool ok = false;
				tp = 0;
				for (int j = 0; j < 4 && !ok; j++) {
					if (!err[i^j]) {
						while (tp) {
							mark[stk[tp--]] = false;
						}
						ok |= dfs(i^j);
					}
				}
				if (!ok) {
					return false;
				}
			}
		}
		return true;
	}
} solver;

char dna[N];
int p[N];

int ID(char c) {
	return c == 'A' ? 0 : c == 'G' ? 1 : c == 'T' ? 2 : 3;
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int n, m;
	while (scanf("%d %d", &n, &m) == 2 && n+m) {
		solver.init(n);
		scanf("%s", dna);
		for (int i = 1; i <= m; i++) {
			int L;
			scanf("%d%*c", &L);
			for (int j = 1; j <= L; j++) {
				scanf("%d", &p[j]);
			}
			for (int l = 1, r = L; l < r; l++, r--) {
				for (int k = 0; k < 4; k++) {
					solver.add_edge(p[l]*4+k, p[r]*4+k);
				}
			}
		}
		for (int i = 0; i < n; i++) {
			solver.draw(i*4+(ID(dna[i])+2)%4);
		}
		for (int i = 1; i < n; i++) {
			int u = ID(dna[i-1]), v = ID(dna[i]);
			for (int j = 1; j < 4; j++) {
				int tu = (u+j) % 4, tv = (v+j) % 4;
				solver.add_edge((i-1)*4+tu, i*4+v);
				solver.add_edge(i*4+tv, (i-1)*4+u);
			}
		}
		printf("%s\n", solver.solve() ? "YES" : "NO");
	}
	return 0;
}