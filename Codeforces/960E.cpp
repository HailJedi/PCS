#include <bits/stdc++.h>
#define pb push_back
#define root 1

using namespace std;

typedef long long ll;

const int N = 200010;
const ll P = 1e9+7;

vector<int> g[N];
int n, u, v;
ll V[N], dpth[N], fa[N], o[N], e[N];
ll ans;

void dfs(int u, int d) {
	dpth[u] = d;
	for (auto v: g[u]) {
		if (v != fa[u]) {
			fa[v] = u;
			dfs(v, d+1);
			(ans += 2*(o[u]*e[v]-e[u]*o[v])*V[u]) %= P;
			(e[u] += o[v]) %= P;
			(o[u] += e[v]) %= P;
		}
	}
	o[u]++;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &V[i]);
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &u, &v);
		g[u].pb(v); g[v].pb(u);
	}
	dfs(root, 0);
	for (int i = 1; i <= n; i++) {
		if (dpth[i]&1) 
			ans += 2*(o[i]*(e[root]-o[i]+1) % P - e[i]*(o[root]-e[i]) % P) % P * V[i] % P;
		else 
			ans += 2*(o[i]*(o[root]-o[i]+1) % P - e[i]*(e[root]-e[i]) % P) % P * V[i] % P;
		((ans -= V[i]) += P) %= P;
	}
	printf("%lld\n", (ans+P) % P);
	return 0;
}