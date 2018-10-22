/*
Created 2018-10-22
"USACO 2017 February Contest, Platinum
Problem 2. Why Did the Cow Cross the Road II"
A DP solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int n;
vector<int> adj[N];
int pos[N];
int a[N], b[N];

struct SegmentTree {
	struct Node {
		Node *ls, *rs;
		int l, r;
		int mx;
		void *operator new(size_t, int l, int r) {
			static Node pool[N*10], *p = pool;
			Node *ret = p++;
			ret->l = l;
			ret->r = r;
			ret->ls = ret->rs = 0x0;
			ret->mx = 0;
			return ret;
		}
	} *root;

	void build(Node *&o) {
		if (o->l != o->r) {
			int mid = (o->l + o->r) / 2;
			o->ls = new (o->l, mid) Node;
			o->rs = new (mid+1, o->r) Node;
			build(o->ls);
			build(o->rs);
		}
	}
	
	void build() {
		root = new (1, n) Node;
		build(root);
	}

	void update(Node *&o, int p, int v) {
		if (o->l == o->r) {
			o->mx = max(o->mx, v);
		} else {
			if (p <= o->ls->r) {
				update(o->ls, p, v);
			} else {
				update(o->rs, p, v);
			}
			o->mx = max(o->ls->mx, o->rs->mx);
		}
	}

	void update(int p, int v) {
		update(root, p, v);
	}

	int max_val(Node *o, int p) {
		if (o->r <= p) {
			return o->mx;
		}
		int ret = max_val(o->ls, p);
		if (o->rs != 0x0 && o->rs->l <= p) {
			ret = max(ret, max_val(o->rs, p));
		}
		return ret;
	}

	int max_val(int p) {
		if (p == 0) {
			return 0;
		}
		return max_val(root, p);
	}
} seg;

int main() {
	freopen("nocross.in", "r", stdin);
	freopen("nocross.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {	
		scanf("%d", &a[i]);
		pos[a[i]] = i;
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &b[i]);
		for (int d = -4; d <= 4; d++) {
			if (b[i] + d >= 1 && b[i] + d <= n) {
				adj[i].push_back(pos[b[i]+d]);
			}
		}
		sort(adj[i].begin(), adj[i].end(), greater<int>());
	}
	seg.build();
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < (int)adj[i].size(); j++) {
			seg.update(adj[i][j], seg.max_val(adj[i][j]-1) + 1);
		}
	}
	printf("%d\n", seg.max_val(n));
	return 0;
}
