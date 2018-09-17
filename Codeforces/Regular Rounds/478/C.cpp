#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 200010;
int n, q;
ll a[N], k[N], sum[N];
ll lp, rst;

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> q;
	for (int i = 1; i <= n; i++) { cin >> a[i]; sum[i] = sum[i-1] + a[i]; }
	for (int i = 1; i <= q; i++) cin >> k[i];
	lp = 1, rst = 0;
	for (int t = 1; t <= q; t++) {
		ll dmg = k[t];
		if (dmg >= rst + sum[n] - sum[lp-1]) { cout << n << endl; lp = 1; rst = 0; continue; }
		ll rst_hp = rst + sum[n] - sum[lp-1] - dmg;
		ll l = 0, r = n+1;
		while (r - l > 1) {
			int mid = (r + l) >> 1;
			if (sum[n] - sum[mid-1] > rst_hp) l = mid;
			else r = mid;
		}
		lp = r; rst = rst_hp - (sum[n] - sum[lp-1]);	
		cout << n - lp + 1 + (rst > 0) << endl;
	}
	return 0;
}