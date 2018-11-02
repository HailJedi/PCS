#include <bits/stdc++.h>

using namespace std;

int chi(long long x) {
	if (x % 4 == 1) {
		return 1;
	} else
	if (x % 4 == 3) {
		return -1;
	} else {
		return 0;
	}
}

int main() {
	long long n;
	cin >> n;
	n *= n;
	long long ans = 1;
	for (long long i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			long long t = 1;
			long long j = 1;
			while (n % i == 0) {
				n /= i;
				j *= i;
				t += chi(j);
			}		
			ans *= t;
		}
	}
	cout << 4 * ans << endl;
	return 0;
}