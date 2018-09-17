#include <bits/stdc++.h>
#define lson(x) (x<<1ll)
#define rson(x) (x<<1ll|1ll)
#define fa(x) (x>>1ll)
#define root 1

using namespace std;

typedef long long ll;

const ll LOG = 60;
const ll MAX = (1ll<<LOG);

ll shft[LOG<<1ll], lay[LOG<<1ll];
ll q, t, x, k;

inline void mod(ll &x, ll m) {
	if (x >= 0) x %= m;
	else x = -(-x)%m;
}

inline ll layer(ll x) {
	return ll(log2(x));
}

void shift(ll x, ll k) {
	ll l = layer(x);
	if (l >= LOG) return;
	shft[l] += k;
	mod(shft[l], lay[l]);
}

inline void tickle(ll &x, ll l) {
	while (x >= lay[l+1]) x -= lay[l];
	while (x < lay[l]) x += lay[l];
}

void print(ll x) {
	while (x) {
		printf("%lld ", x);
		if (x == root) break;
		ll l = layer(x);
		x += shft[l];
		tickle(x, l);
		x = fa(x);
	}
	puts("");
}

int main() {
	for (ll i = 1, j = 0; i <= MAX; i <<= 1ll, j++) lay[j] = i;
	scanf("%lld", &q);
	while (q--) {
		scanf("%lld %lld", &t, &x);
		if (t == 1) {
			scanf("%lld", &k);
			shift(x, k);
			shift(lson(x), -2*k);
		} else 
		if (t == 2) {
			scanf("%lld", &k);
			shift(x, k);
		} else 
		if (t == 3) {
			print(x);
		}
	}
	return 0;
}