#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;
const int M = 5e5+5;
const int INF = 1e9;
int v[3*N], c[N];

struct unit {
	int l, r, lp, rp, lm, rm, d, a, b;
	void init(int x) {
		d = -INF;
		b = v[x] == -1;
		a = v[x] == -2;
		lp = lm = rp = rm = -INF * (v[x] <= 0 || c[v[x]] == 0);
	}
} uni[12*N];

vector<int> g[N];
int n, dark, ct, q, x;
int pos[N];
string s;

void dfs(int u, int f) {
	v[++ct] = -1;
	v[++ct] = u;
	pos[u] = ct;
	for (int i = 0; i < g[u].size(); i++) {
		if (g[u][i] != f) {
			dfs(g[u][i], u);
		}
	}
	v[++ct] = -2;
}

int max(int a, int b, int c) {
	return max(a, max(b, c));
}

int max(int a, int b, int c, int d) {
	return max(a, max(b, c, d));
}

unit merge(unit &ls, unit &rs) {
	unit s;
	int a = ls.a, b = ls.b, c = rs.a, d = rs.b;
	s.l = ls.l, s.r = rs.r;
	s.d = max(ls.d, rs.d, ls.rp+rs.lm, ls.rm+rs.lp);
	if (b < c)  {
		s.a = a-b+c, s.b = d;
	} else {
		s.a = a, s.b = b-c+d;
	}
	s.rp = max(rs.rp, ls.rp-c+d, ls.rm+c+d);
	s.rm = max(rs.rm, ls.rm+c-d);
	s.lp = max(ls.lp, rs.lp+a-b, rs.lm+a+b);
	s.lm = max(ls.lm, rs.lm-a+b);
	return s;
}

void build(int o, int l, int r) {
	if (l == r) {
		uni[o].l = l;
		uni[o].r = r;
		uni[o].init(l);
	} else {
		int mid = (l+r)/2;
		build(o<<1, l, mid);
		build(o<<1|1, mid+1, r);
		uni[o] = merge(uni[o<<1], uni[o<<1|1]);
	}
}

void modify(int o, int x) {
	int l = uni[o].l, r = uni[o].r;
	if (l == r) {
		uni[o].init(l);
	} else {
		int mid = (l+r)/2;
		modify(o<<1|(x > mid), x);
		uni[o] = merge(uni[o<<1], uni[o<<1|1]);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	dark = n;
	fill(c+1, c+1+n, 1);
	for (int _ = 1; _ < n; _++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 0);
	build(1, 1, ct);
	cin >> q;
	while (q--) {
		cin >> s;
		if (s[0] == 'C') {
			cin >> x;
			dark += (c[x] ? -1 : 1);
			c[x] ^= 1;
			modify(1, pos[x]);
		} else {
			if (dark <= 1) {
				puts(dark ? "0" : "-1");
			} else {
				cout << uni[1].d << endl;
			}
		}
	}
	return 0;
}