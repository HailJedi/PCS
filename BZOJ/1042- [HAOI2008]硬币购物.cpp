#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;
long long dp[N];
int d[4], c[4];
int tot, s;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	dp[0] = 1;
	for (int i = 0; i < 4; i++) {
		cin >> c[i];
		for (int j = c[i]; j < N; j++) {
			dp[j] += dp[j - c[i]];
		}
	}
	cin >> tot;
	while (tot--) {
		for (int i = 0; i < 4; i++) {
			cin >> d[i];
		}
		cin >> s;
		long long ans = 0;
		for (int i = 0; i < 16; i++) {
			int t = s;
			for (int j = 0; j < 4; j++) {
				if ((i >> j) & 1) {
					t -= (d[j] + 1) * c[j];
				}
			}
			long long val = t >= 0 ? dp[t] : 0;
			int bits = __builtin_popcount(i);
			ans += val * (bits & 1 ? -1 : 1);
		}
		cout << ans << endl;
	}
	return 0;
}