#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll INF = 2e18;
const int N = 1e6+5;
ll x[N], y[N], w[N];
ll n, lf, rt, up, dn, cost;

void Count(ll lx, ll ly, ll rx, ll ry) {
	ll cst = 0;
	for (int i = 1; i <= n; i++) {
		if (lx <= x[i] && x[i] <= rx && ly <= y[i] && y[i] <= ry) {
			continue;
		}
		if (lx <= y[i] && y[i] <= rx && ly <= x[i] && x[i] <= ry) {
			cst += w[i];
		} else {
			return;
		}
	}
	cost = min(cost, cst);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	lf = INF, rt = -INF, up = -INF, dn = INF;
	for (int i = 1; i <= n; i++) {
		cin >> x[i] >> y[i] >> w[i];
		ll a = max(x[i], y[i]), b = min(x[i], y[i]);
		lf = min(lf, a), rt = max(rt, a);
		up = max(up, b), dn = min(dn, b);
	}
	cost = INF;
	Count(lf, dn, rt, up);
	Count(lf, dn, up, rt);
	Count(dn, lf, rt, up);
	Count(dn, lf, up, rt);
	cout << 2ll * (rt - lf + up - dn) << ' ' << cost << endl;
	return 0;
}