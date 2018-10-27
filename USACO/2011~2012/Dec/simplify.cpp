/*
Created 2018-10-26
"USACO 2011 December Contest, Gold Division
Problem 2. Simplifying the Farm"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 40000 + 5;
const int M = 100000 + 5;
const int L = 1000000 + 5;
const int mod = 1000000007;

int n, m;
int use[L];
tuple<int, int, int> edge[M];

int fa[N], sz[N];
int cpy[N], good[N];

void init() {
	for (int i = 1; i <= n; i++) {
		fa[i] = i;
		sz[i] = 1;
	}
}

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void unite(int x, int y) {
	if (sz[x] < sz[y]) {
		fa[x] = y;
		sz[y] += sz[x];
	} else {
		fa[y] = x;
		sz[x] += sz[y];
	}
}

int mul(int x, int y) {
	x = 1LL * x * y % mod;
	return x;
}

int main() {
	freopen("simplify.in", "r", stdin);
	freopen("simplify.out", "w", stdout);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		edge[i] = make_tuple(w, u, v);
	}
	sort(edge+1, edge+1+m);
	init();
	long long ct = 0, wt = 0;
	for (int i = 1; i <= m && ct < n-1; i++) {
		int u = find(get<1>(edge[i])), v = find(get<2>(edge[i]));
		if (u != v) {
			unite(u, v);
			ct++;
			int w = get<0>(edge[i]);
			use[w]++;
			wt += w;
		}
	}
	int ans = 1;
	init();
	for (int i = 1, j = 1; i <= m; i = j) {
		j++;
		if (use[get<0>(edge[i])]) {
			while (j <= m && get<0>(edge[i]) == get<0>(edge[j])) {
				j++;
			}
			int s = j - i, cnt = 0;
			memcpy(cpy, fa, sizeof (int) * (n+1));
			for (int p = 1; p < (1 << s); p++) {
				if (__builtin_popcount(p) == use[get<0>(edge[i])]) {
					bool ok = true;
					memcpy(fa, cpy, sizeof (int) * (n+1));
					for (int q = 0; q < s; q++) {
						if ((p >> q) & 1) {
							int u = find(get<1>(edge[i+q]));
							int v = find(get<2>(edge[i+q]));
							if (u != v) {
								unite(u, v);
							} else {
								ok = false;
								break;
							}
						}
					}
					if (ok) {
						cnt++;
						if (cnt == 1) {
							memcpy(good, fa, sizeof (int) * (n+1));
						}
					}
				}
			}
			memcpy(fa, good, sizeof (int) * (n+1));
			ans = mul(ans, cnt);
		}
	}
	printf("%lld %d\n", wt, ans);
	return 0;
}
