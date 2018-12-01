/*
Created 2018-12-01
"博物馆"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 20 + 5;
const int S = 400 + 5;

double p[N];
bool g[N][N];
int deg[N];
int n, m, a, b;

vector<double> solve(vector< vector<double> > &f) {
	for (int i = 0; i < n*n; i++) {
		double t = f[i][i];
		for (int j = i; j <= n*n; j++) {
			f[i][j] /= t;
		}
		for (int j = 0; j < n*n; j++) if (j != i) {
			double t = f[j][i];
			for (int k = i; k <= n*n; k++) {
				f[j][k] -= f[i][k] * t;
			}
		}
	}
	vector<double> ans(n*n);
	for (int i = 0; i < n*n; i++) {
		ans[i] = f[i][n*n];
	}
	return ans;
}

int main() {
	scanf("%d %d %d %d", &n, &m, &a, &b);
	a--, b--;
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--, v--;
		g[u][v] = g[v][u] = 1;
		deg[u]++, deg[v]++;
	}
	for (int i = 0; i < n; i++) {
		g[i][i] = 1;
	}
	for (int i = 0; i < n; i++) {
		scanf("%lf", &p[i]);
	}
	vector< vector<double> > f(n*n, vector<double>(n*n+1, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int st = i * n + j;
			f[st][st] = 1;
			for (int x = 0; x < n; x++) if (g[x][i]) {
				for (int y = 0; y < n; y++) if (g[y][j] && x != y) {
					int st2 = x * n + y;
					double p1 = (x == i ? p[i] : (1 - p[x]) / deg[x]);
					double p2 = (y == j ? p[j] : (1 - p[y]) / deg[y]);
					f[st][st2] -= p1 * p2;
				}
			}
		}
	}
	f[a*n+b][n*n] = 1;
	vector<double> ans = solve(f);
	for (int i = 0; i < n; i++) {
		printf("%.6lf ", ans[i*n+i]);
	}
	return 0;
}
