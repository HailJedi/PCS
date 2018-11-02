#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 70;

ll sr, sb, sg, m, p, n;
ll fac[maxn], rev[maxn];

ll Pow(ll a, ll n) {
	ll b = 1;
	while (n) {
		if (n & 1) b = b * a % p;
		a = a * a % p;
		n >>= 1;
	}
	return b;
}

int main() {
	scanf("%lld %lld %lld %lld %lld", &sr, &sb, &sg, &m, &p);
	n = sr + sb + sg;
	fac[0] = 1;
	for (int i = 1; i <= n; i++)
		fac[i] = fac[i-1] * i % p;
	rev[n] = Pow(fac[n], p-2);
	for (int i = n; i; i--) rev[i-1] = rev[i] * i % p;
	ll ans = fac[n] * rev[sr] % p * rev[sb] % p * rev[sg] % p * Pow(m+1, p-2) % p;
	printf("%lld\n", ans);

	return 0;
}