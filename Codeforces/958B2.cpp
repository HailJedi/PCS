#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int N = 100010;

vector<int> g[N];
vector<int> vec;
int n, root;
int dist[N], fa[N], ans[N], h[N], son[N];
bool mark[N];

void dfs1(int u, int f) {
	dist[u] = dist[f] + 1;
	if (dist[u] > dist[root]) root = u;
	for (auto v: g[u]) {
		if (v != f) {
			dfs1(v, u);
		}
	}
}

void dfs2(int u, int f) {
	h[u] = 1;
	fa[u] = f;
	vec.push_back(u);
	for (auto v: g[u]) {
		if (v != f) {
			dfs2(v, u);
			if (h[v] + 1 > h[u]) {
				h[u] = h[v]+1;
				son[u] = v;
			}
		}
	}
}

bool cmp(int i, int j) {
	return h[i] > h[j];
}

int main() {
	scanf("%d", &n);
	int u, v;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs1(1, 0);
	dfs2(root, 0);
	sort(vec.begin(), vec.end(), cmp);
	ans[1] = 1; mark[root] = true;
	int it = 0;
	for (int i = 2; i <= n; i++) {
		int cnt = 0;
		while (it < vec.size() && mark[vec[it]]) it++;
		if (it == vec.size()) break;
		u = vec[it];
		while (u && !mark[u]) {
			cnt++;
			mark[u] = true;
			u = son[u];
		}
		ans[i] = ans[i-1] + cnt;
		if (ans[i] == n) break;
	}
	for (int i = 1; i <= n; i++)
		printf("%d ", ans[i] ? ans[i] : n);
	puts("");
	return 0;
}