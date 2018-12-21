/*
Created 2018-12-13
"[Poi2000]公共串"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 10;

int n, m;
int lg[N];
char str[N];
int sa[N], rk[N], ht[N];
int st[N][30];

struct Triple {
	int id, x, y;
	Triple() {}
	Triple(int id, int x, int y) : id(id), x(x), y(y) {}
	bool operator < (const Triple &tr) const {
		return x != tr.x ? x < tr.x : y < tr.y;
	}
} temp[N];

bool cmp(int i, int j) {
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
		ht[rk[i]] = k;
	}
	for (int i = 1; i <= n; i++) {
		st[i][0] = ht[i];
	}
	for (int j = 1; (1<<j) <= n; j++) {
		for (int i = 1; i <= n; i++) {
			st[i][j] = min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
		}
	}
	for (int i = 1, k = 0; i <= n; i++) {
		while ((1<<(k+1)) <= i) {
			k++;
		}
		lg[i] = k;
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

char s[N];
int bel[N];
int sum[N][6];

bool allin(int l, int r) {
	for (int i = 1; i <= m; i++) {
		if (sum[r][i] - sum[l-1][i] == 0) {
			return false;
		}
	}
	return true;
}

bool check(int p, int len) {
	int L = p, R = p;
	int l = 0, r = p;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		if (LCP(p, mid) >= len) {
			r = mid;
		} else {
			l = mid;
		}
	}
	L = r;
	l = p, r = n+1;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		if (LCP(p, mid) >= len) {
			l = mid;
		} else {
			r = mid;
		}
	}
	R = l;
	return allin(L, R);
}

int main() {
	scanf("%d", &m);
	n = 0;
	for (int i = 1; i <= m; i++) {
		scanf("%s", s+1);
		int len = strlen(s+1);
		for (int j = 1; j <= len; j++) {
			str[++n] = s[j];
			bel[n] = i;
		}
		if (i != m) {
			str[++n] = '|';
		}
	}
	build();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			sum[i][j] = sum[i-1][j] + (bel[sa[i]] == j);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (bel[sa[i]]) {
			int l = 0, r = n+1;
			while (r - l > 1) {
				int mid = (l + r) / 2;
				if (check(i, mid)) {
					l = mid;
				} else {
					r = mid;
				}
			}
			ans = max(ans, l);
		}
	}
	printf("%d\n", ans);
	return 0;
}