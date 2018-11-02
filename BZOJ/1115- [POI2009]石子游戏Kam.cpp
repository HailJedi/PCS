#include <bits/stdc++.h>

using namespace std;

const int N = 1e3+5;
int a[N];
int n, t;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		int ans = 0;
		for (int i = n; i > 0; i -= 2) {
			ans ^= a[i] - a[i-1];
		}
		puts(ans ? "TAK" : "NIE");
	}
	return 0;
}