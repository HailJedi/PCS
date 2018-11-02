#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll LG = 33;
const ll N = 1e5+5;
map<ll, ll> ct;
ll c[N], d[LG];
ll n, m;
vector<ll> w;

bool borrow(int cur) {
	for (int i = cur + 1; i <= m; i++) {
		if (d[i]) {
			d[cur] += w[i] / w[cur];
			d[i]--;
			return true;
		}
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	w.resize(m+1);
	for (int i = 1; i <= n; i++) {
		cin >> c[i];
	}
	for (int i = 1; i <= m; i++) {
		cin >> w[i];
		ct[w[i]]++;
	}
	sort(w.begin(), w.end());
	w.resize(unique(w.begin(), w.end()) - w.begin());
	m = w.size()-1;
	for (int i = 1; i <= n; i++) {
		for (int j = m; j >= 1; j--) {
			d[j] += c[i] / w[j];
			c[i] %= w[j];
		}
	}
	ll ans = 0;
	for (ll i = 1; i <= m; i++) {
		while (d[i] < ct[w[i]] && borrow(i));
		ans += min(d[i], ct[w[i]]);
	}
	cout << ans << endl;
	return 0;
}