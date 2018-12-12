/*
Created 2018-12-12
"Uva10829L-gap字符串"
*/

#pragma C++ optimize(2)

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int n, m;
char str[N];
int lg[N];

class SufArray {
	public:
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
	}

	int LCP(int a, int b) {
		a = rk[a], b = rk[b];
		if (a > b) {
			swap(a, b);
		}
		a++;
		int k = lg[b-a+1];
		return min(st[a][k], st[b-(1<<k)+1][k]);
	}
} sa, rsa;

int main() {
	scanf("%d %s", &m, str+1);
	n = strlen(str+1);
	for (int i = 1, k = 0; i <= n; i++) {
		while ((1<<(k+1)) <= i) {
			k++;
		}
		lg[i] = k;
	}
	sa.build();
	for (int i = 1, j = n; i <= j; i++, j--) {
		swap(str[i], str[j]);
	}
	rsa.build();
	long long ans = 0;
	for (int len = 1; 2*len+m <= n; len++) {
		for (int l = 1, r = 1+len+m; r <= n; l += len, r += len) {
			int lcp = min(len, sa.LCP(l, r));
			int lcs = min(len, rsa.LCP(n+1-l, n+1-r));
			if (lcp+lcs > len) {
				ans += lcp+lcs-len;
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}