/*
Created 2018-12-28
"莫比乌斯函数之和"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e7;
const int mod = 1000000007;
const int invm = 500000004;

map<long long, long long> mp;
long long eu[N];
int prime[N];
bool vis[N];

void init() {
	eu[1] = 1;
	for (int i = 2; i < N; i++) {
		if (vis[i] == 0) {
			eu[i] = i-1;
			prime[++prime[0]] = i;
		}
		for (int j = 1; j <= prime[0] && i * prime[j] < N; j++) {
			vis[i * prime[j]] = 1;
			if (i % prime[j] != 0) {
				eu[i * prime[j]] = eu[i] * (prime[j] - 1) % mod;
			} else {
				eu[i * prime[j]] = eu[i] * prime[j] % mod;
				break;
			}
		}
	}
	for (int i = 2; i < N; i++) {
		(eu[i] += eu[i-1]) %= mod;
	}
}

long long Phi(long long n) {
	if (n < N) {
		return eu[n];
	}
	if (mp.count(n)) {
		return mp[n];
	}
	mp[n] = (n % mod) * ((n+1) % mod) % mod * invm % mod;
	for (long long i = 2, j; i <= n; i = j) {
		j = n / (n / i) + 1;
		(mp[n] -= (j - i) * Phi(n / i) % mod) %= mod;
	}
	return mp[n];
} 

int main() {
	init();
	long long a;
	scanf("%lld", &a);
	printf("%lld\n", (Phi(a) + mod) % mod);
	return 0;
}