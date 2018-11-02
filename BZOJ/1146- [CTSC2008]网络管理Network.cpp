#include <bits/stdc++.h>

using namespace std;

const int N = 8e4+5;

struct SBTree {
	SBTree *ls, *rs;
	int l, r, sum;
	void *operator new (size_t, SBTree *ls, SBTree *rs, int l, int r, int sum) {
		static SBTree pool[N<<7], *p = pool;
		SBTree *ret = p++;
		ret->ls = ls;
		ret->rs = rs;
		ret->l = l;
		ret->r = r;
		ret->sum = sum;
		return ret;
	}
} *root[N], *bit[N];

struct Edge {
	Edge *next;
	int u, v;
	void *operator new (size_t, int u, int v, Edge *next) {
		static Edge pool[N*2], *p = pool;
		Edge *ret = p++;
		ret->u = u;
		ret->v = v;
		ret->next = next;
		return ret;
	}
} *head[N];

void addedge(int u, int v) {
	head[u] = new (u, v, head[u]) Edge;
	head[v] = new (v, u, head[v]) Edge;
}

int n, nn, m, u, v, dt;
int t[N], k[N], a[N], b[N], rk[N*2];
int fa[23][N], depth[N], dfn[N], cls[N];

int tr(int x) {
	return lower_bound(rk+1, rk+1+nn, x) - rk;
}

SBTree *build(int l, int r) {
	SBTree *ret = new (0x0, 0x0, l, r, 0) SBTree;
	if (l != r) {
		int mid = (l + r) / 2;
		ret->ls = build(l, mid);
		ret->rs = build(mid+1, r);
	}
	return ret;
}

SBTree *create(SBTree *pre, int p) {
	SBTree *ret = new (pre->ls, pre->rs, pre->l, pre->r, pre->sum+1) SBTree;
	if (ret->l != ret->r) {
		if (p <= ret->ls->r) {
			ret->ls = create(pre->ls, p);
		} else {
			ret->rs = create(pre->rs, p);
		}
	}
	return ret;
}

void dfs(int u) {
	dfn[u] = ++dt;
	depth[u] = depth[fa[0][u]] + 1;
	root[u] = create(root[fa[0][u]], tr(t[u]));
	for (Edge *e = head[u]; e; e = e->next) {
		if (e->v != fa[0][u]) {
			fa[0][e->v] = u;
			dfs(e->v);
		}
	}
	cls[u] = dt;
}

void recrew(SBTree *&t, int l, int r) {
	if (!t) {
		t = new (0x0, 0x0, l, r, 0) SBTree;
	}
}

void add(SBTree *&t, int p, int v) {
	t->sum += v;
	if (t->l != t->r) {
		int mid = (t->l + t->r) / 2;
		if (p <= mid) {
			recrew(t->ls, t->l, mid);
			add(t->ls, p, v);
		} else {
			recrew(t->rs, mid+1, t->r);
			add(t->rs, p, v);
		}
	}
}

int lowbit(int x) {
	return x & (-x);
}

void add(int p, int pt, int v) {
	for (; p <= n; p += lowbit(p)) {
		add(bit[p], pt, v);
	}
}

vector<SBTree*> btl, btr, btla, btlaf;

void change(vector<SBTree*> &bt, bool d) {
	for (int i = 0; i < bt.size(); i++) {
		if (bt[i]) {
			bt[i] = d ? bt[i]->rs : bt[i]->ls;
		}
	}
}

int sum(vector<SBTree*> &bt) {
	int ret = 0;
	for (int i = 0; i < bt.size(); i++) {
		if (bt[i] && bt[i]->rs) {
			ret += bt[i]->rs->sum;
		}
	}
	return ret;
}

int query(SBTree *lt, SBTree *rt, SBTree *lca, SBTree *fla, int k) {
	if (lt->l == lt->r) {
		return lt->l;
	}
	int sz = lt->rs->sum + rt->rs->sum - lca->rs->sum - fla->rs->sum + sum(btr) + sum(btl) - sum(btla) - sum(btlaf);
	if (k > sz) {
		change(btl, 0);
		change(btr, 0);
		change(btla, 0);
		change(btlaf, 0);
		return query(lt->ls, rt->ls, lca->ls, fla->ls, k - sz);
	} else {
		change(btl, 1);
		change(btr, 1);
		change(btla, 1);
		change(btlaf, 1);
		return query(lt->rs, rt->rs, lca->rs, fla->rs, k);
	}
}

int lca(int u, int v) {
	if (depth[u] < depth[v]) {
		swap(u, v);
	}
	for (int i = 20; i >= 0; i--) {
		if (depth[fa[i][u]] >= depth[v]) {
			u = fa[i][u];
		}
	}
	if (u == v) {
		return u;
	}
	for (int i = 20; i >= 0; i--) {
		if (fa[i][u] != fa[i][v]) {
			u = fa[i][u];
			v = fa[i][v];
		}
	}
	return fa[0][u];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> t[i];
		rk[i] = t[i];
	}
	for (int i = 1; i < n; i++) {
		cin >> u >> v;
		addedge(u, v);
	}
	int tt = n;
	for (int i = 1; i <= m; i++) {
		cin >> k[i] >> a[i] >> b[i];
		if (!k[i]) {
			rk[++tt] = b[i];
		}
	}
	sort(rk+1, rk+1+tt);
	nn = 1;
	for (int i = 2; i <= tt; i++) {
		if (rk[i] != rk[i-1]) {
			rk[++nn] = rk[i];
		}
	}
	root[0] = build(1, nn);
	dfs(1);
	for (int i = 1; i <= n+1; i++) {
		bit[i] = new (0x0, 0x0, 1, nn, 0) SBTree;
	}
	for (int i = 1; i <= 20; i++) {
		for (int u = 1; u <= n; u++) {
			fa[i][u] = fa[i-1][fa[i-1][u]];
		}
	}
	for (int i = 1; i <= m; i++) {
		if (!k[i]) {
			add(dfn[a[i]], tr(t[a[i]]), -1);
			add(cls[a[i]]+1, tr(t[a[i]]), 1);
			t[a[i]] = b[i];
			add(dfn[a[i]], tr(t[a[i]]), 1);
			add(cls[a[i]]+1, tr(t[a[i]]), -1);
		} else {
			int la = lca(a[i], b[i]);
			if (depth[a[i]] + depth[b[i]] - 2 * depth[la] + 1 < k[i]) {
				cout << "invalid request!" << endl;
				continue;
			}
			if (dfn[a[i]] > dfn[b[i]]) {
				swap(a[i], b[i]);
			}
			btl.clear();
			btr.clear();
			btla.clear();
			btlaf.clear();
			for (int j = dfn[a[i]]; j; j -= lowbit(j)) {
				btl.push_back(bit[j]);
			}
			for (int j = dfn[b[i]]; j; j -= lowbit(j)) {
				btr.push_back(bit[j]);
			}
			for (int j = dfn[la]; j; j -= lowbit(j)) {
				btla.push_back(bit[j]);
			}
			for (int j = dfn[fa[0][la]]; j; j -= lowbit(j)) {
				btlaf.push_back(bit[j]);
			}
			cout << rk[query(root[a[i]], root[b[i]], root[la], root[fa[0][la]], k[i])] << endl;
		}
	}
	return 0;
}