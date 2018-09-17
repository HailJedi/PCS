#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
ll n, a, b, x, vx, vy;
map<pii, ll> prl;
map<ll, ll> cld;

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> a >> b;
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		cin >> x >> vx >> vy;
		ans += cld[a*vx-vy] - prl[{vx, vy}];
		cld[a*vx-vy]++;
		prl[{vx, vy}]++;
	}
	cout << ans * 2 << endl;
	return 0;
}