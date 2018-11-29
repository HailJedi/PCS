/*
Created 2018-11-29
"绿豆蛙的归宿"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const int M = 200000 + 5;

struct Edge {
	Edge *next;
	int v, w;
	void *operator new (size_t, Edge *next, int v, int w) {	
		static Edge pool[M], *p = pool;
		Edge *ret = p++;
		ret->next = next;
		ret->v = v;
		ret->w = w;
		return ret;
	}
} *head[N];

void add_edge(int u, int v, int w) {
	head[u] = new (head[u], v, w) Edge;
}

int in[N], out[N];
double f[N];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		add_edge(u, v, w);
		in[v]++;
		out[u]++;
	}
	queue<int> q;
	q.push(1);
	f[1] = 1;
	double ans = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (Edge *e = head[u]; e; e = e->next) {
			f[e->v] += f[u] / out[u];
			ans += e->w * f[u] / out[u];
			if (--in[e->v] == 0) {
				q.push(e->v);
			}
		}
	}
	printf("%.2lf\n", ans);
	return 0;
}
