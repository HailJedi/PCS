/*
Created 2018-12-13
"[Spoj]8093 Sevenk Love Oimaster"
*/

#pragma C++ optimize(2)

#include <bits/stdc++.h>

using namespace std;

const int N = 10000 + 5;
const int Q = 60000 + 5;
const int T = 600000 + 5;

int n, m, pt;
int lg[T];
char s[T], str[T];
int sa[T], rk[T], ht[T];
int st[T][30];

struct Triple {
	int id, x, y;
	Triple() {}
	Triple(int id, int x, int y) : id(id), x(x), y(y) {}
	bool operator < (const Triple &tr) const {
		return x != tr.x ? x < tr.x : y < tr.y;
	}
} temp[T];

bool cmp(int i, int j) {
	return str[i] < str[j];
}

void build() {
	for (int i = 1; i <= pt; i++) {
		sa[i] = i;
	}
	sort(sa+1, sa+1+pt, cmp);
	for (int i = 1; i <= pt; i++) {
		rk[sa[i]] = rk[sa[i-1]] + (str[sa[i-1]] != str[sa[i]]);
	}
	for (int k = 1; k <= pt; k *= 2) {
		for (int i = 1; i <= pt; i++) {
			temp[i] = Triple(i, rk[i], i+k <= pt ? rk[i+k] : 0);
		}
		sort(temp+1, temp+1+pt);
		for (int i = 1; i <= pt; i++) {
			rk[temp[i].id] = rk[temp[i-1].id] + !(temp[i].x == temp[i-1].x && temp[i].y == temp[i-1].y);
		}
	}
	for (int i = 1; i <= pt; i++) {
		sa[rk[i]] = i;
	}
	for (int i = 1, k = 0; i <= pt; i++) {
		k -= k ? 1 : 0;
		int j = sa[rk[i]-1];
		while (str[j+k] == str[i+k]) {
			k++;
		}
		ht[rk[i]] = k;
	}
	for (int i = 1; i <= pt; i++) {
		st[i][0] = ht[i];
	}
	for (int j = 1; (1<<j) <= pt; j++) {
		for (int i = 1; i <= pt; i++) {
			st[i][j] = min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
		}
	}
}

int LCP(int a, int b) {
	if (a > b) {
		swap(a, b);
	}
	a++;
	int k = lg[b-a+1];
	return min(st[a][k], st[b-(1<<k)+1][k]);
}

struct Ask {
	int id, L;
	Ask(int id, int L) : id(id), L(L) {}
};

vector<Ask> ask[T];
int bel[T], own[Q];
int len[Q];
int bef[N];
int ans[Q];

int bit[T];

int lowbit(int x) {
	return x & -x;
}

void add(int p, int v) {
	for (; p < T; p += lowbit(p)) {
		bit[p] += v;
	}
}

int sum(int p) {
	int ret = 0;
	for (; p; p -= lowbit(p)) {
		ret += bit[p];
	}
	return ret;
}

int main() {
	for (int i = 1, k = 0; i < T; i++) {
		while ((1<<(k+1)) <= i) {
			k++;
		}
		lg[i] = k;
	}
	scanf("%d %d", &n, &m);
	pt = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%s", s+1);
		int len = strlen(s+1);
		for (int j = 1; j <= len; j++) {
			str[++pt] = s[j];
			bel[pt] = i;
		}
		str[++pt] = '|';
	}
	for (int i = 1; i <= m; i++) {
		scanf("%s", s+1);
		len[i] = strlen(s+1);
		own[i] = pt+1;
		for (int j = 1; j <= len[i]; j++) {
			str[++pt] = s[j];
		}
		str[++pt] = '|';
	}
	build();
	for (int i = 1; i <= m; i++) {
		int p = rk[own[i]], L = p, R = p;
		int l = 0, r = p;
		while (r - l > 1) {
			int mid = (l + r) / 2;
			if (LCP(p, mid) >= len[i]) {
				r = mid;
			} else {
				l = mid;
			}
		}
		L = r;
		l = p, r = pt+1;
		while (r - l > 1) {
			int mid = (l + r) / 2;
			if (LCP(p, mid) >= len[i]) {
				l = mid;
			} else {
				r = mid;
			}
		}
		R = l;
		ask[R].push_back(Ask(i, L));
	}
	for (int i = 1; i <= pt; i++) {
		if (bel[sa[i]]) {
			if (bef[bel[sa[i]]]) {
				add(bef[bel[sa[i]]], -1);
			}
			add(i, 1);
			bef[bel[sa[i]]] = i;
		}
		for (int j = 0; j < (int)ask[i].size(); j++) {
			Ask a = ask[i][j];
			ans[a.id] = sum(i) - sum(a.L-1);
		}
	}
	for (int i = 1; i <= m; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}