#include <bits/stdc++.h>

using namespace std;

const int N = 200;
int n;
int a[N];

int main() {
	cin >> n;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		ans += abs(a[i]);
	}
	cout << ans << endl;
	return 0;
}