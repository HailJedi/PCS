#include <bits/stdc++.h>

using namespace std;

const int N = 16;
const int X = 100+5;

int f[1<<N][X];
int sum[1<<N];
int a[N];

int dp(int s, int x) {
	if (f[s][x] != -1) {	
		return f[s][x];
	}
	if (__builtin_popcount(s) == 1) {
		return f[s][x] = 1;
	}
	int y = sum[s] / x;
	for (int s0 = s & (s-1); s0; s0 = (s0-1) & s) {
		int s1 = s ^ s0;
		if (sum[s0] % x == 0 && dp(s0, min(x, sum[s0]/x)) && dp(s1, min(x, sum[s1]/x))) {
			return f[s][x] = 1;
		}
		if (sum[s0] % y == 0 && dp(s0, min(y, sum[s0]/y)) && dp(s1, min(y, sum[s1]/y))) {
			return f[s][x] = 1;
		}
	}
	return f[s][x] = 0;
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int n, x, y, kase = 0;
	while (cin >> n && n) {
		cin >> x >> y;
		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}
		int whole = (1 << n) - 1;
		for (int i = 0; i <= whole; i++) {
			sum[i] = 0;
			for (int j = 0; j < n; j++) {
				if (i & (1 << j)) {
					sum[i] += a[j];
				}
			}
		}
		int ans = -1;
		if (x * y != sum[whole] || sum[whole] % x != 0) {
			ans = 0;
		} else {
			memset(f, -1, sizeof f);
			ans = dp(whole, min(x, y));
		}
		cout << "Case " << ++kase << ": " << (ans ? "Yes" : "No") << endl;
	}
	return 0;
}
		