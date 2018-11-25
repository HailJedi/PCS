#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 100+5;
const ll INF = 1e18;

ll a[N], sum[N];
ll f[N][N][2];

void update(ll &x, ll y, int p) {
	if (p) {
		x = max(x, y);
	} else {
		x = min(x, y);
	}
}

ll dp(ll l, ll r, int p) {
	if (l > r) {
		return 0;
	}	
	
	ll &ret = f[l][r][p];

	if (ret != -1) {
		return ret;
	}

	int s = p ? 1 : -1;

	ret = -s * INF;

	for (int i = l; i <= r; i++) {
		update(ret, s * (sum[i] - sum[l-1]) + dp(i+1, r, p^1), p);
	}
	for (int i = r; i >= l; i--) {
		update(ret, s * (sum[r] - sum[i-1]) + dp(l, i-1, p^1), p);
	}
	
	return ret;
}

int n;

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	while (cin >> n && n) {

		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			sum[i] = sum[i-1] + a[i];
		}

		memset(f, -1, sizeof f);
		
		cout << dp(1, n, 1) << endl;
	}
	
	return 0;
}