/*
Created 2018-10-20
"String Journey"
A DP + string structure solution
(TLE)
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 500000 + 5;
const int INF = 1e9;

int n;
char s[N];
int dp[N];

int sa[N], rk[N], h[N];
pair<pair<int, int>, int> tmp[N];

bool cmp_sa(int i, int j) {
	return s[i] < s[j];
}

void build_sa() {
	for (int i = 1; i <= n; i++) {
		sa[i] = i;
	}
	sort(sa+1, sa+1+n, cmp_sa);
	rk[sa[1]] = 1;
	for (int i = 2; i <= n; i++) {
		rk[sa[i]] = rk[sa[i-1]] + (s[sa[i-1]] != s[sa[i]]);
	}
	for (int k = 1; k <= n; k *= 2) {
		for (int i = 1; i <= n; i++) {
			int sec = i + k <= n ? rk[i+k] : 0;	
			tmp[i] = make_pair(make_pair(rk[i], sec), i);
		}
		sort(tmp+1, tmp+1+n);
		rk[tmp[1].second] = 1;
		for (int i = 2; i <= n; i++) {
			rk[tmp[i].second] = rk[tmp[i-1].second] + !(tmp[i-1].first == tmp[i].first);
		}
	}
	for (int i = 1; i <= n; i++) {
		sa[rk[i]] = i;
	}
}

void build_lcp() {
	int k = 0;
	h[1] = 0;
	for (int i = 2; i <= n; i++) {
		if (rk[i] == 1) {
			continue;
		}
		int j = sa[rk[i]-1];
		while (s[i+k] != s[j+k]) {
			k--;
		}
		while (s[i+k] == s[j+k]) {
			k++;
		}
		h[rk[i]] = k;
	}
}

struct SegTree {
	struct Node {
		Node *ls, *rs;
		int mx, mn;
		int l, r;
		void *operator new(size_t, int l, int r) {
			static Node pool[N*10], *p = pool;
			Node *ret = p++;
			ret->ls = 0x0;
			ret->rs = 0x0;
			ret->l = l;
			ret->r = r;
			ret->mn = INF;
			ret->mx = -INF;
			return ret;
		}
	} *root;
	
	void build(Node *&o, int *val) {
		if (o->l == o->r) {
			o->mn = o->mx = val[o->l];
		} else {
			int mid = (o->l + o->r) / 2;
			o->ls = new (o->l, mid) Node;
			o->rs = new (mid+1, o->r) Node;
			build(o->ls, val);
			build(o->rs, val);
			o->mx = max(o->ls->mx, o->rs->mx);
			o->mn = min(o->ls->mn, o->rs->mn);
		}
	}
	
	void build(int *val) {
		root = new (1, n) Node;
		build(root, val);
	}

	int min_val(Node *o, int ql, int qr) {
		if (ql <= o->l && o->r <= qr) {
			return o->mn;
		}
		int ret = INF;
		int mid = (o->l + o->r) / 2;
		if (mid >= ql) {
			ret = min(ret, min_val(o->ls, ql, mid));
		}
		if (mid+1 <= qr) {
			ret = min(ret, min_val(o->rs, mid+1, qr));
		}
		return ret;
	}

	int min_val(int ql, int qr) {
		return min_val(root, ql, qr);
	}

	int max_val(Node *o, int ql, int qr) {
		if (ql <= o->l && o->r <= qr) {
			return o->mx;
		}
		int ret = -INF;
		int mid = (o->l + o->r) / 2;
		if (mid >= ql) {
			ret = max(ret, max_val(o->ls, ql, mid));
		}
		if (mid+1 <= qr) {
			ret = max(ret, max_val(o->rs, mid+1, qr));
		}
		return ret;
	}

	int max_val(int ql, int qr) {
		return max_val(root, ql, qr);
	}

	void change(Node *&o, int p, int v) {
		if (o->l == o->r) {
			o->mx = o->mn = v;
		} else {
			int mid = (o->l + o->r) / 2;
			if (p <= mid) {
				change(o->ls, p, v);
			} else {
				change(o->rs, p, v);
			}
			o->mx = max(o->ls->mx, o->rs->mx);
			o->mn = min(o->ls->mn, o->rs->mn);
		}
	}

	void change(int p, int v) {
		change(root, p, v);
	}
	
} seg_dp, seg_sa;

bool judge(int l, int r, int tar) {
	if (l == r) {
		return n - l + 1 >= tar;
	}
	return seg_sa.min_val(l+1, r) >= tar;
}

bool check(int i, int k) {
	int lp = -1, rp = -1;
	int l = 0, r = rk[i];
	while (r - l > 1) {
		int mid = (l + r) / 2;
		if (judge(mid, rk[i], k)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	lp = r;
	l = rk[i], r = n+1;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		if (judge(rk[i], mid, k)) {
			l = mid;
		} else {
			r = mid;
		}
	}
	rp = l;
	return seg_dp.max_val(lp, rp) >= dp[i]-1;
}

int main() {
	scanf("%d %s", &n, s+1);
	build_sa();
	build_lcp();
	seg_sa.build(h);
	seg_dp.build(dp);
	int pt = n+1;
	dp[n] = 1;
	for (int i = n-1; i >= 1; i--) {
		dp[i] = dp[i+1] + 1;
		while (!check(i, dp[i]-1) && !check(i+1, dp[i]-1) && dp[i] > 1) {
			dp[i]--;
			seg_dp.change(--pt, dp[pt]);
		}
	}
	cout << endl;
	printf("%d\n", *max_element(dp+1, dp+1+n));	
	return 0;
}
	
