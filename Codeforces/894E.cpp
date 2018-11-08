/*
Created 2018-11-08
"Ralph and Mushrooms"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;
const int M = 1000000 + 5;

int head[N], u[M], v[M], nxt[M];
long long w[M];

void add_edge(int e, int _u, int _v, int _w) {
	u[e] = _u;
	v[e] = _v;
	w[e] = _w;
	nxt[e] = head[_u];
	head[_u] = e;
}

int low[N], dfn[N], dt;
int scc_no[N], scc_cnt;
stack<int> stk;

void dfs(int u) {
	dfn[u] = low[u] = ++dt;
	stk.push(u);
	for (int e = head[u]; e; e = nxt[e]) {
		if (!dfn[v[e]]) {
			dfs(v[e]);
			low[u] = min(low[u], low[v[e]]);
		} else 
		if (!scc_no[v[e]]) {
			low[u] = min(low[u], dfn[v[e]]);
		}
	}
	if (low[u] == dfn[u]) {
		scc_cnt++;
		while (true) {
			int x = stk.top();
			stk.pop();
			scc_no[x] = scc_cnt;
			if (x == u) {
				break;
			}
		}
	}
}

long long f[N], bon[N], sum[N], sum2[N];

long long solve(int u) {
	if (f[u] != -1) {
		return f[u];
	}
	f[u] = 0;
	for (int e = head[u]; e; e = nxt[e]) {
		f[u] = max(f[u], solve(v[e]) + w[e]);
	}
	return (f[u] += bon[u]);
}

int main() {
	int n, m, s;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		add_edge(i, u, v, w);
	}
	scanf("%d", &s);
	dfs(s);
	memset(head, 0, sizeof head);
	for (int i = 1; i < N; i++) {
		sum[i] = sum[i-1] + i;
		sum2[i] = sum2[i-1] + sum[i];
	}
	int e = 0;
	for (int i = 1; i <= m; i++) {
		if (scc_no[u[i]] != scc_no[v[i]]) {
			add_edge(++e, scc_no[u[i]], scc_no[v[i]], w[i]);
		} else {
			int l = 0, r = N;
			while (r - l > 1) {
				int mid = (l + r) / 2;
				if (w[i] >= sum[mid]) {
					l = mid;
				} else {
					r = mid;
				}
			}
			bon[scc_no[u[i]]] += (l+1) * w[i] - sum2[l];
		}
	}
	memset(f, -1, sizeof f);
	printf("%lld\n", solve(scc_no[s]));
	return 0;
}
