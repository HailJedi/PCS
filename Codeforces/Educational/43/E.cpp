#include <bits/stdc++.h>

using namespace std;

const int N = 200010;
typedef long long ll;
ll n, a, b, p;

struct creature {
	ll dmg, hp;
	creature() {}
	bool operator < (const creature &t) const {
		return hp - dmg > t.hp - t.dmg;
	}
} crt[N];

bool mark[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> a >> b;
	for (int i = 0; i < n; i++) 
		cin >> crt[i].hp >> crt[i].dmg;
	p = 1 << a;
	ll ans = 0;
	for (int i = 0; i < n; i++)
		ans += crt[i].dmg;
	if (b) {
		sort(crt, crt+n);
		ll v = 0;
		int lst = -1;
		for (int i = 0; i < n; i++) {
			v += i < b ? max(crt[i].hp, crt[i].dmg) : crt[i].dmg;
			if (i < b && crt[i].hp >= crt[i].dmg) mark[i] = 1, lst = i;
		}
		ans = max(ans, v);
		if (a) {
 			for (int i = 0; i < n; i++) {
				ll u = v;
				if (!mark[i]) {
					(u -= crt[i].dmg) += crt[i].hp * p;
					if (~lst && i >= b) (u -= crt[lst].hp) += crt[lst].dmg;
				} else {
					(u -= crt[i].hp) += crt[i].hp * p;
				}
				ans = max(ans, u);
			}
		}
	}
	cout << ans << endl;

	return 0;
}