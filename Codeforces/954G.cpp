#include <bits/stdc++.h>

#define N 500010
#define INF (1ll<<62)

using namespace std;

typedef long long ll;
ll a[N], b[N], n, r, k, j;

bool check(ll mid) {
	ll res = k;
	for (int i = 1; i <= n; i++) b[i] = a[i];
	for (int i = 1; i <= n; i++) {
		b[i] += b[i-1];
		if (b[i] <= mid) {
			if (mid - b[i] > res) return false;
			res -= mid - b[i];
			b[min(n+1, i+2*r+1)] -= mid - b[i];
			b[i] = mid;
		}
	}
	return true;
}

int main() {
	scanf("%lld %lld %lld", &n, &r, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &j);
		a[max(1ll, i-r)] += j;
		a[min(n+1, i+r+1)] -= j;
	}
	ll l = 0, r = INF;
	while (r - l > 1) {
		ll mid = (l + r) >> 1ll;
		if (check(mid)) l = mid;
		else r = mid;
	}
	printf("%lld\n", check(r) ? r : l);
	return 0;
}