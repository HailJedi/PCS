/*
Created 2018-12-15
"串"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 200000 + 5;

int n, m, k;
char str[N], s[N];
int lg[N];

class SufArray {
	public:
	int sa[N], rk[N], ht[N];
	int st[N][30];

	struct Triple {
		int id;
		long long x;
		Triple() {}
		Triple(int id, long long x) : id(id), x(x) {}
		bool operator < (const Triple &tr) const {
			return x < tr.x;
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
				temp[i].id = i;
				temp[i].x = 1LL * rk[i] * N + (i+k <= n ? rk[i+k] : 0);
			}
			sort(temp+1, temp+1+n);
			for (int i = 1; i <= n; i++) {
				rk[temp[i].id] = rk[temp[i-1].id] + (temp[i].x != temp[i-1].x);
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
		if (a > b) {
			swap(a, b);
		}
		if (a == b) {
			return n-sa[a]+1;
		}
		a++;
		int k = lg[b-a+1];
		return min(st[a][k], st[b-(1<<k)+1][k]);
	}
} sa;

class Multiset {
	public:
	int in[N];
	int sz;
	void insert(int v) {
		sz += (++in[v] == 1);
	}
	void erase(int v) {
		sz -= (--in[v] == 0);
	}
	int size() {
		return sz;
	}
} st;

int bel[N], tail[N];
long long ans[N];
int Right[N];

int main() {
	for (int i = 1, k = 0; i < N; i++) {
		while ((1 << (k+1)) <= i) {
			k++;
		}
		lg[i] = k;
	}
	scanf("%d %d", &m, &k);
	n = 0;
	for (int i = 1; i <= m; i++) {
		scanf("%s", s+1);
		int len = strlen(s+1);
		for (int j = 1; j <= len; j++) {
			str[++n] = s[j];
			bel[n] = i;
		}
		tail[i] = n+1;
		if (i != m) {
			str[++n] = '|';
		}
	}
	sa.build();
	for (int i = 1, j = 1; i <= n; i++) {
		while (j <= n && st.size() < k) {
			if (bel[sa.sa[j]]) {
				st.insert(bel[sa.sa[j]]);
			}
			j++;
		}
		Right[i] = st.size() >= k ? j-1 : N;
		if (bel[sa.sa[i]]) {
			st.erase(bel[sa.sa[i]]);
		}
	}
	for (int i = 1; i <= n; i++) {
		if (str[sa.sa[i]] != '|') {
			int l = 0, r = tail[bel[sa.sa[i]]]-sa.sa[i]+1;
			while (r - l > 1) {
				int lim = (l + r) / 2;
				int L = i, R = i;
				int lp = 0, rp = i;
				while (rp - lp > 1) {
					int pos = (lp + rp) / 2;
					if (sa.LCP(pos, i) >= lim) {
						rp = pos;
					} else {
						lp = pos;
					}
				}
				L = rp;
				lp = i, rp = n+1;
				while (rp - lp > 1) {
					int pos = (lp + rp) / 2;
					if (sa.LCP(pos, i) >= lim) {
						lp = pos;
					} else {
						rp = pos;
					}
				}
				R = lp;
				if (Right[L] <= R) {
					l = lim;
				} else {
					r = lim;
				}
			}
			ans[bel[sa.sa[i]]] += l;
		}
	}
	for (int i = 1; i <= m; i++) {
		printf("%lld ", ans[i]);
	}
	return 0;
}