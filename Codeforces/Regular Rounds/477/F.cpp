#include <bits/stdc++.h>
using namespace std;

#define s 0
#define t (n+1)

typedef long long ll;

const int N = 50010;
const ll E = 1e7;
const ll INF = 1e18;

ll n, m, ct;
ll u[N], v[N], a[N], b[N], c[N], d[N];
ll hd[N], nxt[N], to[N], cp[N];
ll dst[N], que[N], cur[N];
ll head, tail;

void link(int u, int v, ll c) {
	to[++ct] = v; cp[ct] = c;
	nxt[ct] = hd[u]; hd[u] = ct;
}

bool bfs() {
	for (int i = s; i <= t; i++) dst[i] = 0;
	dst[s] = 1;
	head = 0, tail = 1;
	que[++head] = s;
	while (head <= tail) {
		int u = que[head++];
		for (int i = hd[u]; i; i = nxt[i]) {
			int v = to[i];
			if (!dst[v] && cp[i] > 0) {
				dst[v] = dst[u] + 1;
				que[++tail] = v;
				if (v == t) break;
			}
		}
	}
	return dst[t];
}

ll dfs(ll u, ll f) {
	if (u == t || f == 0) return f;
	ll vf = 0;
	for (ll &i = cur[u]; i; i = nxt[i]) {
		if (cp[i] > 0 && dst[to[i]] == dst[u]+1) {
			ll fl = dfs(to[i], min(f, cp[i]));
			if (fl) {
				cp[i] -= fl;
				cp[i^1] += fl;
				f -= fl;
				vf += fl;
				if (!f) break;
			}
		}
	}
	return vf;
}

ll dinic() {
	ll ret = 0;
	while (bfs()) {
		for (int i = s; i <= t; i++) cur[i] = hd[i];
		while (ll f = dfs(s, INF)) ret += f;
	}
	return ret;
}

ll flow(ll x) {
	ll ret = 0; ct = 1;
	for (int i = s; i <= t; i++) hd[i] = 0;
	for (int i = 1; i <= m; i++) {
		ll lb = a[i]*x+b[i], ub = c[i]*x+d[i]; 
		ret += lb;
		link(s, v[i], lb); link(v[i], s, 0);
		link(u[i], t, lb); link(t, u[i], 0);
		link(u[i], v[i], ub-lb); link(v[i], u[i], 0);
	}
	return ret - dinic();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u[i] >> v[i] >> a[i] >> b[i] >> c[i] >> d[i];
		b[i] *= E; d[i] *= E;
	}
	int l = 0, r = E;
	while (r - l >= 3) {
		int df = (r-l)/3;
		if (flow(l+df) < flow(r-df)) r -= df;
		else l += df;
	}
	ll mf = flow(l);
	for (int i = l+1; i <= r; i++) {
		if (ll f = flow(i) < mf) { mf = f; l = i; }
	}
	if (mf > 0) return puts("0"), 0;
	int lp = 0, rp = l-1;
	while (lp <= rp) {
		int m = (lp+rp)/2;
		if (flow(m) > 0) lp = m+1;
		else rp = m-1;
	}
	ll ans = -lp;
	lp = l+1, rp = E;
	while (lp <= rp) {
		int m = (lp+rp)/2;
		if (flow(m) > 0) rp = m-1;
		else lp = m+1;
	}
	ans += rp;
	cout << fixed << setprecision(10) << (double)ans/E << endl;
	return 0;
}