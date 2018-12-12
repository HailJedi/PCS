/*
Created 2018-12-11
"识别子串"
*/

#pragma C++ optimize(2)

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const int INF = 1e9;

class SegTree {
public:
	struct Node {
		Node *ls, *rs;
		int tag, mn;
		int l, r;
		void *operator new(size_t, int l, int r) {
			static Node pool[N*5], *p = pool;
			Node *ret = p++;
			ret->l = l;
			ret->r = r;
			ret->mn = INF;
			ret->tag = INF;
			return ret;
		}
	} *root;

	int n;

	void build(Node *o) {
		if (o->l != o->r) {
			int mid = (o->l + o->r) / 2;
			o->ls = new (o->l, mid) Node;
			o->rs = new (mid+1, o->r) Node;
			build(o->ls);
			build(o->rs);
		}
	}

	void init(int n) {
		this->n = n;
		root = new (1, n) Node;
		build(root);
	}

	void update(int &x, int y) {
		x = min(x, y);
	}

	void pushdown(Node *o) {
		update(o->ls->tag, o->tag);
		update(o->rs->tag, o->tag);
		update(o->ls->mn, o->ls->tag);
		update(o->rs->mn, o->rs->tag);
		o->tag = INF;
	}

	void change(Node *o, int l, int r, int v) {
		if (l <= o->l && o->r <= r) {
			update(o->tag, v);
			update(o->mn, v);
		} else {
			pushdown(o);
			int mid = (o->l + o->r) / 2;
			if (mid >= l) {
				change(o->ls, l, r, v);
			}
			if (r > mid) {
				change(o->rs, l, r, v);
			}
		}
	}

	void change(int l, int r, int v) {
		change(root, l, r, v);
	}

	int min_val(Node *o, int p) {
		if (o->l == o->r) {
			return o->mn;
		} else {
			int mid = (o->l + o->r) / 2;
			pushdown(o);
			if (p <= mid) {
				return min_val(o->ls, p);
			} else {
				return min_val(o->rs, p);
			}
		}
	}

	int min_val(int p) {
		return min_val(root, p);
	}

} sg, sg2;

char str[N];

class SufArray {
public:
	int sa[N], rk[N], ht[N];
	int n;

	void init() {
		scanf("%s", str+1);
		n = strlen(str+1);
	}

	struct Triple {
		int id, x, y;
		Triple() {}
		Triple(int id, int x, int y) : id(id), x(x), y(y) {}
		bool operator < (const Triple &tr) const {
			return x != tr.x ? x < tr.x : y < tr.y;
		}
	} temp[N];

	static bool cmp(int i, int j) {
		return str[i] < str[j];
	}

	void build() {
		for (int i = 1; i <= n; i++) {
			sa[i] = i;
		}
		sort(sa+1, sa+1+n, cmp);
		for (int i = 1; i <= n; i++) {
			rk[sa[i]] = rk[sa[i-1]] + (str[sa[i-1]] != str[sa[i]]);
		}
		for (int k = 1; k <= n; k *= 2) {
			for (int i = 1; i <= n; i++) {
				temp[i] = Triple(i, rk[i], i+k <= n ? rk[i+k] : 0);
			}
			sort(temp+1, temp+1+n);
			for (int i = 1; i <= n; i++) {
				rk[temp[i].id] = rk[temp[i-1].id] + !(temp[i].x == temp[i-1].x && temp[i].y == temp[i-1].y);
			}
		}
		for (int i = 1; i <= n; i++) {
			sa[rk[i]] = i;
		}
		for (int i = 1, k = 0; i <= n; i++) {
			k -= k ? 1 : 0;
			int j = sa[rk[i]-1];
			while (str[j+k] == str[i+k]) {
				k++;
			}
			ht[i] = k;
		}
	}

	void solve() {
		build();
		sg.init(n);
		sg2.init(n);
		for (int i = 1; i <= n; i++) {
			int len = max(ht[i], ht[sa[rk[i]+1]]);
			if (i+len <= n) {
				sg.change(i, i+len, len+1);
				sg2.change(i+len, n, -i);
			}
		}
		for (int i = 1; i <= n; i++) {
			printf("%d\n", min(sg.min_val(i), sg2.min_val(i)+i+1));
		}
		puts("");
	}
} sa;

int n;

int main() {
	sa.init();
	sa.solve();
	return 0;
}