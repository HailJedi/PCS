#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
#define pb push_back

using namespace std;

typedef unsigned long long ll;
const ll MAX = 1e18;
vector<ll> vec, v;
int q;
ll l, r;

ll root(ll x) {
	ll l = 0, r = 1e9;
	while (r - l > 1) {
		ll mid = (r+l)>>1;
		if (mid * mid <= x) l = mid;
		else r = mid;
		if (l * l == x) break;
	}
	return l;
}

void generate() {
	for (ll i = 2; i <= 1e6; i++) 
		for (ll p = i*i*i; ; p = p * i * i) {
			ll r = root(p);
			if (r * r != p) vec.pb(p);
			if (p > MAX / (i * i)) break;
		}
	sort(all(vec));
	vec.erase(unique(all(vec)), vec.end());
}

inline ll num_between(ll l, ll r) {
	return upper_bound(all(vec), r) - lower_bound(all(vec), l);
}

inline ll perfect_2(ll l, ll r) {
	return root(r) - root(l-1);
}

int main() {
	generate();
	cin >> q;
	while (q--) {
		cin >> l >> r;
		cout << num_between(l, r) + perfect_2(l, r) << endl;
	}
	return 0;
}