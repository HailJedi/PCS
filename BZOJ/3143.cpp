/*
Created 2018-11-30
"[Hnoi2013]游走"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 500 + 5;
const int M = 500000 + 5;

int n, m;

struct Edge {
	Edge *next;
	int v, id;
	void *operator new(size_t, Edge *next, int v, int id) {
		static Edge pool[M], *pt = pool;
		Edge *ret = pt++;
		ret->next = next;
		ret->v = v;
		ret->id = id;
		return ret;
	}
} *head[N];

void add_edge(int u, int v, int id) {
	head[u] = new (head[u], v, id) Edge;
	head[v] = new (head[v], u, id) Edge;
}

int deg[N];
double f[M];

vector<double> solve(vector< vector<double> > &func) {
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j <= n; j++) {
			func[i][j] /= func[i][i];
		}
		func[i][i] = 1;
		for (int j = 0; j < n; j++) if (j != i) {
			for (int k = i+1; k <= n; k++) {
				func[j][k] -= func[i][k] * func[j][i];
			}
			func[j][i] = 0;
		}
	}
	vector<double> ans(n);
	for (int i = 0; i < n; i++) {
		ans[i] = func[i][n];
	}
	return ans;
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--, v--;
		add_edge(u, v, i);
		deg[u]++;
		deg[v]++;
	}
	vector< vector<double> > func(n, vector<double>(n+1, 0));
	for (int i = 0; i < n; i++) {
		func[i][i] = -1;
		for (Edge *e = head[i]; e; e = e->next) if (e->v != n-1) {
			func[i][e->v] = 1.0 / deg[e->v];
		}
	}
	func[0][n] = -1;
	vector<double> sol = solve(func);
	for (int u = 0; u < n-1; u++) {
		for (Edge *e = head[u]; e; e = e->next) {
			f[e->id] += sol[u] / deg[u];
		}
	}
	sort(f+1, f+1+m);
	double ans = 0;
	for (int i = 1; i <= m; i++) {
		ans += (m-i+1) * f[i];
	}
	printf("%.3lf\n", ans);
	return 0;
}