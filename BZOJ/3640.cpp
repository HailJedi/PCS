/*
Created 2018-11-30
"JC的小苹果"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 150 + 5;
const int M = 5000 + 5;
const int H = 10000 + 5;

struct Edge {
	Edge *next;
	int j;
	Edge (Edge *next = NULL, int j = 0) : next(next), j(j) {}
} pool[M*2], *pt = pool, *head[N];

void add_edge(int i, int j) {
	head[i] = new (pt++) Edge(head[i], j);
}

int n, m, hp;

void solve(vector< vector<double> > &func, vector< vector<double> > &cnst) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) if (j != i) {
			double t = func[j][i] / func[i][i];
			for (int k = i; k < n; k++) {
				func[j][k] -= func[i][k] * t;
			}
			for (int k = 0; k < n; k++) {
				cnst[j][k] -= cnst[i][k] * t;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cnst[i][j] /= func[i][i];
		}
	}
}

int deg[N];
double f[H][N];
double cnst[N];

int main() {
	scanf("%d %d %d", &n, &m, &hp);
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--, v--;
		add_edge(u, v);
		deg[u]++;
		if (u != v) {
			add_edge(v, u);
			deg[v]++;
		}
	}
	vector< vector<double> > func(n, vector<double>(n, 0));
	vector< vector<double> > comat(n, vector<double>(n, 0));
	for (int i = 0; i < n; i++) {
		func[i][i] = 1;
		comat[i][i] = 1;
		if (a[i] == 0) {
			for (Edge *e = head[i]; e; e = e->next) {
				if (e->j != n-1) {
					func[i][e->j] -= 1.0 / deg[e->j];
				}
			}
		}
	}
	solve(func, comat);
	double ans = 0;
	for (int h = hp; h; h--) {
		memset(cnst, 0, sizeof cnst);
		cnst[0] = (h == hp);
		for (int i = 0; i < n; i++) {
			if (a[i] && a[i] + h <= hp) {
				for (Edge *e = head[i]; e; e = e->next) {
					if (e->j != n-1) {
						cnst[i] += f[a[i]+h][e->j] / deg[e->j];
					}
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				f[h][i] += cnst[j] * comat[i][j];
			}
		}
		ans += f[h][n-1];
	}
	printf("%.8lf\n", ans);
	return 0;
}
