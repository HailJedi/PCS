#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) x.size()
typedef vector<int> vi;

const int N = 2010;
const int INF = 1e9;

int n;
int a[N], b[N];
int dp[N][N];

vi disolve(int st) {
	vi ret;
	while (st) {
		ret.pb(st % 10);
		st /= 10;
	}
	return ret;
}

int compress(vi &v, int exc) {
	int ret = 0;
	for (auto e: v) if (e != exc) (ret *= 10) += e;
	return ret;
}

int solve(int p, int st) {
	int &ret = dp[p][st];
	if (ret != -1) return ret;
	ret = INF;
	vi v = disolve(st);
	v.pb(b[p]);
	sort(all(v));
	int nxt = a[p+1], pos = a[p];
	if (p == n) {
		int lp = v.front(), rp = v.back();
		return ret = min(ret, min(abs(pos-lp), abs(pos-rp))+rp-lp);
	}
	if (sz(v) < 4) ret = min(ret, solve(p+1, compress(v, nxt))+abs(nxt-pos));
	for (int i = 0; i < sz(v); i++)
		for (int j = i; j < sz(v); j++) {
			int lp = v[i], rp = v[j];
			int t = min(abs(lp-pos)+abs(rp-nxt), abs(rp-pos)+abs(lp-nxt))+rp-lp;
			int cps = 0;
			for (int k = 0; k < sz(v); k++)
				if ((k < i || k > j) && v[k] != nxt) (cps *= 10) += v[k];
			ret = min(ret, solve(p+1, cps)+t);
		}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i] >> b[i];
	memset(dp, -1, sizeof(dp));
	cout << solve(1, 0) + a[1] - 1 + 2 * n << endl;
	return 0;
}