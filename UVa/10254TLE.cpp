#include <bits/stdc++.h>

using namespace std;

const int N = 1e4+5;

long long f[N];

int main() {
	freopen("read", "r", stdin);
	freopen("write", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	int n;
	while (cin >> n) {
		f[1] = 1;
		for (int i = 2; i <= n; i++) {
			f[i] = 1e18;
			for (int j = 1; j < i; j++) {
				long long t = (long long)pow(2, i-j) - 1 + 2 * f[j];
				if (t > 0) {
					f[i] = min(f[i], t);
				}
			}
		}
		cout << f[n] << endl;
	}
	return 0;
}
