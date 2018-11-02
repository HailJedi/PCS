#include <bits/stdc++.h>

using namespace std;

const int N = 5e4+5;
int n, x, y;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		cin >> x >> y;
		ans += y - x;
	}
	for (int i = 1; i <= n; i++) {
		cin >> x >> y;
		ans += x - y;
	}
	cout << ans << endl;
}