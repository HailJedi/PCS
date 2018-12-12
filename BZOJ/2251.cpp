/*
Created 2018-12-12
"[2010Beijing Wc]外星联络"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 10000 + 5;

int n;
char s[N];
int sa[N], rk[N], ht[N];
int st[N][30], lg[N];

struct Triple {
	int id, x, y;
	Triple() {}
	Triple(int id, int x, int y) : id(id), x(x), y(y) {}
	bool operator < (const Triple &tr) const {
		return x != tr.x ? x < tr.x : y < tr.y;
	}
} temp[N];

bool cmp(int i, int j) {
	return s[i] < s[j];
}

void build() {
	for (int i = 1; i <= n; i++) {
		sa[i] = i;
	}
	sort(sa+1, sa+1+n, cmp);
	for (int i = 1; i <= n; i++) {
		rk[sa[i]] = rk[sa[i-1]] + (s[sa[i-1]] != s[sa[i]]);
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
		while (s[j+k] == s[i+k]) {
			k++;
		}
		ht[rk[i]] = k;
	}
	for (int i = 1, k = 0; i <= n; i++) {
		while ((1 << (k+1)) <= i) {
			k++;
		}
		lg[i] = k;
	}
	for (int i = 1; i <= n; i++) {
		st[i][0] = ht[i];
	}
	for (int j = 1; (1<<j) <= n; j++) {
		for (int i = 1; i <= n; i++) {
			st[i][j] = min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
		}
	}
}

int LCP(int a, int b) {
	if (a > b) {
		swap(a, b);
	}
	if (a == b) {
		return st[a][0];
	}
	a++;
	int k = lg[b-a+1];
	return min(st[a][k], st[b-(1<<k)+1][k]);
}

int main() {
	scanf("%d %s", &n, s+1);
	s[0] = -1;
	build();
	for (int i = 1; i <= n; i++) {
		int l = sa[i], r = l + ht[i];
		while (r <= n) {
			int ans = 0;
			int lp = 0, rp = i;
			while (rp - lp > 1) {
				int mid = (lp + rp) / 2;
				if (LCP(mid, i) >= r-l+1) {
					rp = mid;
				} else {
					lp = mid;
				}
			}
			ans += i - rp;
			lp = i, rp = n+1;
			while(rp - lp > 1) {
				int mid = (lp + rp) / 2;
				if (LCP(i, mid) >= r-l+1) {
					lp = mid;
				} else {
					rp = mid;
				}
			}
			ans += lp - i;
			if (++ans > 1) {
				printf("%d\n", ans);
			}
			r++;
		}
	}
	return 0;
}
