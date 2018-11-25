#include <bits/stdc++.h>

using namespace std;

const int N = 1e4+5;

int f[N];
int n, m, K;

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	while (cin >> n >> K >> m && n && K && m) {
		
		f[1] = 1;
		f[2] = 2;
		for (int i = 3; i <= n; i++) {
			int k = (K - 1) % (i - 1) + 1;
			f[i] = f[i-1] + k;
			if (f[i] > i) {
				f[i] -= (i-1);
			}
		}

		int ans = f[n] + m - 1;
		if (ans > n) {
			ans -= n;
		}
		cout << ans << endl;
		
	}

	return 0;
}