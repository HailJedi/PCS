/*
Created 2018-10-22
😣
*/

#include <bits/stdc++.h>

using namespace std;

long long n, a, b, c, d, x0, x1, cnt[2];

int main() {
	cin >> n >> a >> b >> c >> d >> x0;
	for (int i = 1; i <= n; i++) {
		x1 = (a * x0 % d * x0 % d + b * x0 % d + c) % d;
		int par = __builtin_parity(x1);
		cnt[par]++;
		x0 = x1;
	}
	cout << cnt[0] * cnt[1] << endl;
	return 0;
}
