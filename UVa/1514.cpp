#include <bits/stdc++.h>

using namespace std;

const int N = 500 + 5;
const int S = N * N * 8;

struct TwoSAT {
	int n;
	bool mark[S];
	int stk[S], tp;
	vector<int> g[S];
	
	void add_edge(int u, int v) {
		g[u].push_back(v);
	}
	
	void init(int n) {
		this->n = n;
		memset(mark, false, sizeof mark);
		for (int i = 0; i < 2*n; i++) {
			g[i].clear();
		}
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
		for (int i = 0; i < g[x].size(); i++) {
			if (!dfs(g[x][i])) {
				return false;
			}
		}
		return true;
	}
	
	bool solve() {
		for (int i = 0; i < 2*n; i += 2) {
			if (mark[i] && mark[i^1]) {
				return false;
			}
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

const int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const int rev[4] = {1, 0, 3, 2};

int id[N][N];
int idx;
char pat[N][N];

int ID(int x, int y) {
	return id[x][y] == -1 ? id[x][y] = idx++ : id[x][y];
}

int main() {
//  freopen("read", "r", stdin);
//  freopen("write", "w", stdout);
  
  int T;
	scanf("%d", &T);
	while (T--) {
		int n, m;
		scanf("%d %d", &n, &m);
		memset(id, -1, sizeof id);
		int b = 0, w = 0;
		idx = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%s", pat[i]+1);
			for (int j = 1; j <= m; j++) {
				if (pat[i][j] == 'B') {
					b++;
					for (int k = 0; k < 4; k++) {
						ID(i+dir[k][0], j+dir[k][1]);
					}
				} else
				if (pat[i][j] == 'W') {
					w++;
					ID(i, j);
				}
			}
		}
		solver.init(idx*4);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (pat[i][j] == 'B') {
					int up = ID(i+dir[0][0], j+dir[0][1]) * 4 + rev[0];
					int down = ID(i+dir[1][0], j+dir[1][1]) * 4 + rev[1];
					int left = ID(i+dir[2][0], j+dir[2][1]) * 4 + rev[2];
					int right = ID(i+dir[3][0], j+dir[3][1]) * 4 + rev[3];
					solver.add_clause(up, 0, down, 0);
					solver.add_clause(up, 1, down, 1);	
					solver.add_clause(left, 0, right, 0);
					solver.add_clause(left, 1, right, 1);
				} else 
				if (pat[i][j] == 'W') {
					for (int k = 0; k < 4; k++) {
						int u = ID(i, j) * 4 + k;
						for (int t = 1; t <= 3; t++) {
							int v = ID(i, j) * 4 + (k+t)%4;
							solver.add_edge(u*2, v*2+1);
						}
					}
				}
			}
		}
		bool ok = true;
		for (int i = 1; i <= n && ok; i++) {
			for (int j = 1; j <= m && ok; j++) {
				if (pat[i][j] == 'B') {
					for (int k = 0; k < 4 && ok; k++) {
						int x = i+dir[k][0], y = j+dir[k][1];
						if (x <= 0 || x > n || y <= 0 || y > m || pat[x][y] != 'W') {
							int u = ID(x, y) * 4;
							for (int t = 0; t < 4 && ok; t++) {
								if (!solver.dfs((u+t)*2+1)) {
									ok = false;
								}
							}
						}
					}
				} else 
				if (pat[i][j] == 'W') {
					for (int k = 0; k < 4 && ok; k++) {
						int x = i+dir[k][0], y = j+dir[k][1];
						if (x <= 0 || x > n || y <= 0 || y > m || pat[x][y] != 'B') {
							int u = ID(i, j) * 4 + k;
							if (!solver.dfs(u*2+1)) {
								ok = false;
							}
						}
					}
				}
			}
		}
		if (b * 2 != w || !ok || !solver.solve()) {
			printf("NO\n");
		} else {
			printf("YES\n");
		}
	}
  return 0;
}

