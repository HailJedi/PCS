/*
Created 2018-11-21
"Race to 1"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;

double f[N];
vector<int> primes;
bool not_prime[N];

double solve(int n) {
	if (n == 1) {
		return 0;
	}
	if (f[n] != -1) {
		return f[n];
	}
	f[n] = 0;
	int div = 0, tot = 0;
	for (int p: primes) {
		if (p > n) {
			break;
		}
		tot++;
		if (n % p == 0) {
			div++;
			f[n] += solve(n / p);
		}
	}
	f[n] += tot;
	f[n] /= div;
	return f[n];
}

int main() {
	for (int i = 0; i < N; i++) {
		f[i] = -1;
	}
	for (int i = 2; i < N; i++) {
		if (!not_prime[i]) {
			primes.push_back(i);
			for (int j = i * 2; j < N; j += i) {
				not_prime[j] = true;
			}
		}
	}
	int T, n, kase = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		printf("Case %d: %.7lf\n", ++kase, solve(n));
	}
	return 0;
}
