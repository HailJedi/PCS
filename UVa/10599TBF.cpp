#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;

int gar[N][N];
int f[N][N];
int pth[N][N];
long long way[N][N];
vector<int> path;
vector<int> node[N];
int n, m;

void dfs(int r, int c) {
	if (gar[r][c]) {
		path.push_back((r-1) * m + c);
	}
	if (r-1 >= 1 && f[r-1][c] == f[r][c] - gar[r][c]) {
		dfs(r-1, c);
	} else
	if (c-1 >= 1 && f[r][c-1] == f[r][c] - gar[r][c]) {
		dfs(r, c-1);
	} else {
//		assert(false);
	}
}

void update(int &x, int y) {
	if (x < y) {
		x = y;
	}
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int r, c, kase = 0;
	while (scanf("%d %d", &n, &m) == 2 && n != -1) {
		memset(gar, 0, sizeof gar);
		for (int i = 1; i <= n; i++) {
			node[i].clear();
		}
		node[1].push_back(1);
		while (scanf("%d %d", &r, &c) == 2 && r) {
			gar[r][c] = 1;
			if (r+c != 2) {
				node[r].push_back(c);
			}
		}
		for (int i = 1; i <= n; i++) {
			sort(node[i].begin(), node[i].end());
		}
		if (node[n].size() == 0 || node[n].back() != m) {
			node[n].push_back(m);
		}
		memset(f, 0, sizeof f);
		f[1][1] = gar[1][1];
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				update(f[i+1][j], f[i][j] + gar[i+1][j]);
				update(f[i][j+1], f[i][j] + gar[i][j+1]);
			}
		}
		memset(way, 0, sizeof way);
		way[1][1] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (i*j == 1 || gar[i][j]) {
//					cout << i << ' ' << j << ": " << endl;
					int lc = 1e9;
					for (int k = i; k <= n; k++) {
						vector<int>::iterator it = lower_bound(node[k].begin(), node[k].end(), j);
						if (k == i) {
							it = ++it;
						}
						if (it != node[k].end() && *it < lc) {
//							cout << k << ' ' << *it << endl;
							if (f[k][*it] == f[i][j] + 1) {
								way[k][*it] += way[i][j];
							}
							lc = *it;
						}
					}
				}
			}
		}
		path.clear();
		dfs(n, m);
		printf("CASE#%d: %d %lld ", ++kase, f[n][m], way[n][m]);
		for (int i = path.size()-1; i > 0; i--) {
			printf("%d ", path[i]);
		}
		printf("%d\n", path[0]);
	}
	return 0;
}