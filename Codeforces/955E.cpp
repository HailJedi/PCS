#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
#define N 100010
#define INF 1e9

using namespace std;

typedef long long ll;

struct SPT {
	vector<vector<ll>> dp;
	vector<int> log;
	int n;
	SPT(int n) : n(n) {
		log.resize(n+1);
		for (int i = 2; i <= n; i++) log[i] = log[i/2]+1;
		dp.resize(20);
		for (int i = 0; i < 20; i++) {
			dp[i].resize(n+1);
			fill(all(dp[i]), INF);
		}
	}
	void init(vector<int> &a) {
		for (int i = 1; i <= n; i++) dp[0][i] = a[i];
		for (int k = 1; (1<<k) <= n; k++) 
			for (int i = 1; i + (1<<k) <= n+1; i++) {
				int lval = dp[k-1][i], rval = dp[k-1][i+(1<<(k-1))];
				dp[k][i] = min(lval, rval);
			}
	}
	int minv(int l, int r) {
		assert(l <= r);
		int k = log[r-l+1];
		int lval = dp[k][l], rval = dp[k][r-(1<<k)+1];
		return min(lval, rval);
	}
};

int main() {
	int n;
	cin >> n;
	vector<int> a(n+1);
	for (int i = 1; i <= n; i++) cin >> a[i];

	auto S = SPT(n);
	S.init(a);

	vector<int> la(n+1);
	auto LS = SPT(n);
	for (int i = 1; i <= n; i++) la[i] = a[i] - i;
	LS.init(la);
	auto RS = SPT(n);
	for (int i = 1; i <= n; i++) la[i] = a[i] + i;
	RS.init(la);
	
	int ans = INF, L = 1;
	for (int T = 1; T <= n; T++) {
		while (L <= T && T >= 2 * L - a[L]) L++;
		int j = 0;
		if (L <= T) j = L;
		else {
			int lx = T, rx = n;
			int idx = 0;
			while (lx <= rx) {
				int mx = (lx + rx) >> 1;
				if (S.minv(T, mx) >= T) 
					lx = mx + 1;
				else 
					idx = mx, rx = mx - 1;
			}
			if (!idx) continue;
			j = idx;
		}
		int lmin, rmin;
		if (j <= T) {
			lmin = LS.minv(1, j-1) + T;
			rmin = min(LS.minv(j, T) + T, RS.minv(T, n) - T);
		} else {
			lmin = min(LS.minv(1, T) + T, RS.minv(T, j-1) - T);
			rmin = RS.minv(j, n) - T;
		}
		ans = min(ans, max(lmin, rmin));
	}

	if (ans != INF) cout << ans;
	else cout << -1;
	puts("");
	return 0;
}