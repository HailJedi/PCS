#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define sz(x) (x.size())
#define all(x) x.begin(), x.end()
#define fs first
#define sc second

using namespace std;

const int N = 500010;
const int INF = 1e9;

int n, m, K;
string s, t;
int fa[N], rfa[N];
int len[N], pos[N];
int rlen[N], rpos[N];
vector<pair<int, int> > ans;
void calc_fa() {
	fa[1] = 0;
	int k = 0;
	for (int i = 2; i <= m; i++) {
		while (k >= 1 && t[k+1] != t[i]) k = fa[k];
		if (t[k+1] == t[i]) k++;
		fa[i] = k;
	}
}

void calc_rfa() {
	rfa[m] = m+1;
	int k = m+1;
	for (int i = m-1; i >= 1; i--) {
		while (k <= m && t[k-1] != t[i]) k = rfa[k];
		if (t[k-1] == t[i]) k--;
		rfa[i] = k;
	}
}

void calc_len() {
	int k = 0;
	for (int i = 1; i <= n; i++) {
		while (k >= 1 && t[k+1] != s[i]) k = fa[k];
		if (t[k+1] == s[i]) k++;
		len[i] = k;
		while (len[i] > K) {
			k = fa[k];
			len[i] = k;
		}
	}
}

void calc_rlen() {
	int k = m+1;
	for (int i = n; i >= 1; i--) {
		while (k <= m && t[k-1] != s[i]) k = rfa[k];
		if (t[k-1] == s[i]) k--;
		rlen[i] = m-k+1;
		while (rlen[i] > K) {
			k = rfa[k];
			rlen[i] = m-k+1;
		}
	}
}

void calc_pos() {
	for (int i = 0; i < N; i++) pos[i] = INF;
	for (int i = K; i <= n-K; i++) {
		int k = len[i];
		if (pos[k] != INF) continue;
		while (k) {
			pos[k] = min(pos[k], i);
			k = fa[k];
			if (pos[k] != INF) break;
		}
	}
}

void calc_rpos() {
	for (int i = 0; i < N; i++) rpos[i] = -INF;
	for (int i = n-K+1; i >= K+1; i--) {
		int k = m-rlen[i]+1;
		if (rpos[m-k+1] != -INF) continue;
		while (k <= m) {
			rpos[m-k+1] = max(rpos[m-k+1], i);
			k = rfa[k];
			if (rpos[m-k+1] != -INF) break;
		}
	}
}

void solve() {
	for (int i = 1; i <= K; i++)
		if (len[i] == m) {
			puts("Yes");
			int l = i-m+1;
			cout << l << ' ' << l+K << endl;
			return;
		}
	for (int i = n-K+1; i <= n; i++) 
		if (rlen[i] == m) {
			puts("Yes");
			int r = n-K+1;
			cout << r-K << ' ' << r << endl;
			return;
		}
	for (int i = 1; i < m; i++) {
		int l1 = i, l2 = m-i;
		if (pos[l1] < rpos[l2] && pos[l1] >= K && rpos[l2] <= n-K+1) {
			puts("Yes");
			cout << pos[l1]-K+1 << ' ' << rpos[l2] << endl;
			return;
		}
	}
	puts("No");
}

void check() {
	for (int i = 1; i <= n; i++) {
		int l = len[i], p = pos[i]-l+1;
		for (int j = 1; j <= l; j++, p++) {
			if (s[p] != t[j]) puts("Error");
		}
	}
	puts("prefix done");
	for (int i = 1; i <= n; i++) {
		int l = rlen[i], p = rpos[i];
		for (int j = m-l+1; j <= m; j++, p++) {
			if (s[p] != t[j]) puts("Error");
		}
	}
	puts("Done");
}

int main() {
	cin >> n >> m >> K;
	cin >> s >> t;
	s = '0' + s;
	t = '0' + t;
	calc_fa();
	calc_len();
	calc_pos();
	calc_rfa();
	calc_rlen();
	calc_rpos();
	// check();
	solve();
}