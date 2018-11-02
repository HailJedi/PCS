#include <bits/stdc++.h>

using namespace std;

const int N = 2e2+5;
const int M = N*N;
const int INF = 1e9;

struct Edge {
	Edge *next, *rev;
	int u, v, c;
	void *operator new (size_t, int u, int v, int c, Edge *next) {
		static Edge pool[M*100], *p = pool;
		Edge *e = p++;
		e->u = u;
		e->v = v;
		e->c = c;
		e->next = next;
		return e;
	}
} *head[N*5] = {0x0}, *cur[N*5] = {0x0};

void addedge(int u, int v, int c) {
	head[u] = new (u, v, c, head[u]) Edge;
	head[v] = new (v, u, 0, head[v]) Edge;
	head[u]->rev = head[v];
	head[v]->rev = head[u];
}

int n, m, u, v, s, t;
int g[N][N];
int d[N*5];

bool bfs() {
	queue<int> q;
	q.push(s);
	memset(d, -1, sizeof(d));
	d[s] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (Edge *e = head[u]; e; e = e->next) {
			if (d[e->v] == -1 && e->c > 0) {
				d[e->v] = d[u] + 1;
				q.push(e->v);
			}
		}
	}
	return d[t] >= 0;
}

int dfs(int u, int f) {
	if (u == t || f == 0) {
		return f;
	}
	int vf = 0;
	for (Edge *&e = cur[u]; e; e = e->next) {
		if (e->c > 0 && d[e->v] == d[u] + 1) {
			int fl = dfs(e->v, min(f, e->c));
			e->c -= fl;
			e->rev->c += fl;
			f -= fl;
			vf += fl;
		}
	}
	return vf;
}

int dinic() {
	int ret = 0;
	while (bfs()) {
		for (int i = s; i <= t; i++) {
			cur[i] = head[i];
		}
		while (int f = dfs(s, INF)) {
			ret += f;
		}
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		g[u][v] = 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= n; k++) {
				if (i != j && j != k && i != k) {
					g[j][k] |= g[j][i] & g[i][k];
				}
			}
		}
	}
	s = 0, t = 2 * n + 1;
	for (int i = 1; i <= n; i++) {
		addedge(s, i, 1);
		addedge(i+n, t, 1);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i != j && g[i][j]) {
				addedge(i, j+n, 1);
			}
 		}
	}
	cout << n - dinic() << endl;
	return 0;
}

// https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1531327410344&di=82d3ed9f3037819649ec2c228b796145&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201601%2F04%2F20160104225038_F2iec.png
