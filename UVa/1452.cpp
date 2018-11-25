#include <bits/stdc++.h>

using namespace std;

int mod(int x, int k) {
	return (x % k + k) % k;
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int T;
	cin >> T;
	while (T--) {
		int n, k, f[3];
		cin >> n >> k;
		f[0] = mod(k % 3 - 1, 3);
		f[1] = mod(f[0] + 1 + mod(k % 2 - 1, 2), 3);
		f[2] = 3 - f[0] - f[1];
		for (int i = 4; i <= n; i++) {
			for (int j = 0; j < 3; j++) {
				(f[j] += k) %= i;
			}
		}
		cout << f[0] + 1 << ' ' << f[1] + 1 << ' ' << f[2] + 1 << endl;
	}
	return 0;
}
		