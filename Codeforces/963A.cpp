#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod = 1e9+9;
const int maxn = 1e9;
const int maxk = 1e5+5;

char sym[maxk];

ll Pow(ll a, ll n) {
	ll b = 1;
	while (n) {
		if (n & 1) b = b * a % mod;
		 a = a * a % mod;
		 n >>= 1;
	}
	return b;
}

int main() {
	ll n, a, b, k;
	
	cin >> n >> a >> b >> k;

	ll co = Pow(Pow(a, mod-2)*b%mod, k);

	if (co == 1) co = (n+1)/k;
	else co = (Pow(co, n/k+1)-1)*Pow(co-1, mod-2)%mod;

	scanf("%s", sym);
	ll ans = 0;
	for (int i = 0; i < k; i++)
		ans += Pow(a, n-i)*Pow(b, i)%mod*co%mod*(sym[i] == '+'? 1 : -1);
	cout << (ans%mod+mod)%mod;

	return 0;
}