/*
Created 2019-1-4
"[Noi2010]能量采集"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

long long f[N];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	if (n > m) {
		swap(n, m);
	}
	long long ans = 0;
	for (int i = n; i; i--) {
		f[i] = 1LL * (n/i) * (m/i);
		for (int j = i*2; j <= n; j += i) {
			f[i] -= f[j];
		}
		ans += f[i] * (2 * i - 1);
	}
	printf("%lld\n", ans);
	return 0;
}