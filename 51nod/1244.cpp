/*
Created 2018-12-28
"莫比乌斯函数之和"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e7;

map<long long, long long> mp;
int mu[N], prime[N];
bool vis[N];

void init() {
	mu[1] = 1;
	for (int i = 2; i < N; i++) {
		if (vis[i] == 0) {
			mu[i] = -1;
			prime[++prime[0]] = i;
		}
		for (int j = 1; j <= prime[0] && i * prime[j] < N; j++) {
			vis[i * prime[j]] = 1;
			if (i % prime[j] != 0) {
				mu[i * prime[j]] = -mu[i];
			} else {
				mu[i * prime[j]] = 0;
				break;
			}
		}
	}
	for (int i = 2; i < N; i++) {
		mu[i] += mu[i-1];
	}
}

long long M(long long n) {
	if (n < N) {
		return mu[n];
	}
	if (mp.count(n)) {
		return mp[n];
	}
	mp[n] = 1;
	for (long long i = 2, j; i <= n; i = j) {
		j = n / (n / i) + 1;
		mp[n] -= (j - i) * M(n / i);
	}
	return mp[n];
} 

int main() {
	init();
	long long a, b;
	scanf("%lld %lld", &a, &b);
	printf("%lld\n", M(b) - M(a-1));
	return 0;
}