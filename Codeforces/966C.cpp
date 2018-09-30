#include <bits/stdc++.h>

using namespace std;

#define N 100010
#define lgn 60
#define pb push_back
#define head 1
#define end 0
#define sz(x) x.size()

typedef long long ll;

vector<ll> vec[lgn+1];
ll v, val[N];
int n, cur = 1;
int nxt[N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &v);
		for (ll j = lgn; j >= 0; j--)
			if ((1ll << j) & v) { vec[j].pb(v); break; }
	}

	ll s = lgn;
	for (ll j = lgn; j >= 0; j--) {
		if (sz(vec[j]) >= 2) return puts("No"), 0;
		if (sz(vec[j]) == 1) { val[head] = vec[j][0]; s = j-1; break; }
	}

	if (!val[head]) return puts("No"), 0;

	for (ll j = s; j >= 0; j--) {
		if (!sz(vec[j])) continue;
		val[++cur] = val[head];
		nxt[cur] = nxt[head];
		nxt[head] = cur;
		val[head] = *vec[j].begin();
		vec[j].erase(vec[j].begin());
		for (int it = nxt[head]; it != end && sz(vec[j]); it = nxt[it]) {
			if (val[it] & (1ll << j)) {
				nxt[++cur] = nxt[it];
				nxt[it] = cur;
				val[cur] = *vec[j].begin();
				vec[j].erase(vec[j].begin());
				it = cur;
			}
		}
		if (sz(vec[j])) return puts("No"), 0;
	}
	puts("Yes");
	for (int it = head; it != end; it = nxt[it])
		printf("%lld ", val[it]);
	puts("");

	return 0;
}