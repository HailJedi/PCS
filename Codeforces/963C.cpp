#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll N = 200010;

ll n;
map<ll, ll> matrix[N], rowid, colid;
vector<ll> divi;
ll h[N], w[N];
ll r, c;

ll gcd(ll a, ll b) {
	return !b ? a : gcd(b, a%b);
}

int main() {
	scanf("%lld", &n);
	ll w, h, d;
	for (ll i = 1; i <= n; i++) {
		scanf("%lld %lld %lld", &w, &h, &d);
		if (!rowid.count(h)) 
			rowid[h] = ++r;
		if (!colid.count(w)) 
			colid[w] = ++c;
		matrix[rowid[h]][colid[w]] = d;
	}

	for (ll i = 1; i <= r; i++) {
		if (matrix[i].size() != c) {
			puts("0");
			return 0;
		}
	}

	for (int i = 1; i <= r; i++)
		for (int j = 1; j <= c; j++) {
			ll c00 = matrix[1][1], c01 = matrix[1][j];
			ll c10 = matrix[i][1], c11 = matrix[i][j];
			ll d1 = gcd(c00, c10), d2 = gcd(c01, c11);
			c00 /= d1; c10 /= d1; 
			c01 /= d2; c11 /= d2;
			if (c00 != c01 || c10 != c11) {
				puts("0");
				return 0;
			}
		}

	ll divh = matrix[1][1], divw = matrix[1][1];
	for (ll i = 1; i <= c; i++) 
		divh = gcd(divh, matrix[1][i]);
	for (ll i = 1; i <= r; i++) 
		divw = gcd(divw, matrix[i][1]);

	ll ans = 0, g = matrix[1][1];
	for (ll d = 1; d*d <= g; d++)
		if (g%d == 0) {
			ll b = g / d;
			if (divh % d == 0 && divw % b == 0) 
				ans++;
			if (b != d && divh % b == 0 && divw % d == 0) 
				ans++;
		}

	cout << ans << endl;

	return 0;
}