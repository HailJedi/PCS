#include <bits/stdc++.h>

using namespace std;

const int N = 500000 + 5;

int n, m;
char str[N];
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
		a = rk[a], b = rk[b];
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

int main() {
	freopen("read.in", "r", stdin);
	for (int i = 1, k = 0; i < N; i++) {
		while ((1 << (k+1)) <= i) {
			k++;
		}
		lg[i] = k;
	}
	return 0;
}