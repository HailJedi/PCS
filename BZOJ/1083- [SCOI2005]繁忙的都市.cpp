#include <bits/stdc++.h>

using namespace std;

const int N = 305;
const int M = N * N;
int n, m;
struct edge {
	int u, v, w;
	edge() {}
	bool operator < (const edge &e) const {
		return w < e.w;
	}
} eg[M];

int fa[N], rk[N];

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void unite(int x, int y) {
	x = find(x), y = find(y);
	if (x != y) {
		if (rk[x] < rk[y]) {
			rk[y] += rk[x];
			fa[x] = y;
		} else {
			rk[x] += rk[y];
			fa[y] = x;
		}
	}
}

bool same(int x, int y) {
	return find(x) == find(y);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> eg[i].u >> eg[i].v >> eg[i].w;
	}
	sort(eg+1, eg+1+m);
	for (int i = 1; i <= n; i++) {
		rk[i] = 1;
		fa[i] = i;
	}
	cout << n-1 << ' ';
	int cnt = 0, ans;
	for (int i = 1; i <= m; i++) {
		int u = eg[i].u, v = eg[i].v;
		if (!same(u, v)) {
			unite(u, v);
			cnt++;
			if (cnt == n-1) {
				ans = eg[i].w;
				break;
			}
		}
	}
	cout << ans << endl;
	return 0;
}