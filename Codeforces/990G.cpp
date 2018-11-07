/*
Created 2018-11-07
"GCD Counting"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 2e5;
vector<int> g[N];
int a[N];
long long ans[N+1];
int n, x, y;

int gcd(int a, int b) {
	if (a == 0) return b;
	return !b ? a : gcd(b, a % b);
}

map<int, long long> gcds[N];

void dfs(int u, int f) {
	for (auto v: g[u]) {
		if (v != f) {
			dfs(v, u);
			for (auto e: gcds[u]) {
				for (auto f: gcds[v]) {
					ans[gcd(e.first, f.first)] += e.second * f.second;
				}
			}
			for (auto e: gcds[v]) {
				gcds[u][gcd(e.first, a[u])] += e.second;
			}
			gcds[v].clear();
		}
	}
	gcds[u][a[u]]++;
	for (auto e: gcds[u]) {
		ans[e.first] += e.second;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	int maxv = 0;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		maxv = max(a[i], maxv);
	}
	for (int i = 1; i < n; i++) {
		cin >> x >> y;
		x--; y--;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(0, -1);
	for (int i = 1; i <= maxv; i++) {
		if (ans[i]) {
			cout << i << ' ' << ans[i] << endl;
		}
	}
	return 0;
}
