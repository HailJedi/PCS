#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod = 1000000007;
const int maxn = 200010;

ll sum, n, k, w;
ll f[maxn], inf[maxn];

ll p(ll a, ll n) {
	if (!~a)
		return n & 1 ? -1 : 1;
	ll b = 1;
	while (n) {
		if (n & 1) (b *= a) %= mod;
		(a *= a) %= mod;
		n >>= 1;
	}
	return b;
}

ll c(ll n, ll k) {
	if (k > n || n < 0) return 0;
	if (k == 0 || n == k) return 1;
	return f[n] * inf[k] % mod * inf[n-k] % mod;
}

ll stirling(ll n, ll k) {
	ll ret = 0;
	for (ll j = 0; j <= k; j++) 
		(ret += p(-1, k+j) * c(k, j) % mod * p(j, n) % mod) %= mod;
	return ret * inf[k] % mod;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> w;
		(sum += w) %= mod;
	}

	f[0] = inf[0] = 1;
	for (int i = 1; i <= n; i++) {
		f[i] = f[i-1] * i % mod;
		inf[i] = inf[i-1] * p(i, mod-2) % mod;
	}

	ll coe1 = stirling(n, k) % mod;
	ll coe2 = stirling(n-1, k) * (n-1) % mod;

	cout << ((coe1 + coe2 + mod) % mod * sum % mod + mod) % mod << endl;

	return 0;
}