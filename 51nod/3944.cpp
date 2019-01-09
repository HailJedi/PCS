/*
Created 2018-12-28
"Sum"
*/

#pragma C++ optimize(2)

#include <bits/stdc++.h>

using namespace std;

const int N = 2000000;

long long n;
long long mp1[N], mp2[N];
long long phi[N], mu[N];
int prime[N];
bool vis[N];

void init() {
	phi[1] = 1;
	mu[1] = 1;
	for (int i = 2; i < N; i++) {
		if (vis[i] == 0) {
			phi[i] = i-1;
			mu[i] = -1;
			prime[++prime[0]] = i;
		}
		for (int j = 1; j <= prime[0] && 1LL * i * prime[j] < N; j++) {
			vis[i * prime[j]] = 1;
			if (i % prime[j] != 0) {
				mu[i * prime[j]] = -mu[i];
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			} else {
				mu[i * prime[j]] = 0;
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
		}
	}
	for (int i = 2; i < N; i++) {
		phi[i] += phi[i-1];
		mu[i] += mu[i-1];
	}
}

long long Phi(long long x) {
	return x < N ? phi[x] : mp1[n / x];
}

long long Mu(long long x) {
	return x < N ? mu[x] : mp2[n / x];
}

void solve(long long x) {
	if (x < N) {
		return;
	}
	int t = n / x;
	if (vis[t]) {
		return;
	}
	vis[t] = true;
	mp1[t] = x * (x+1) / 2;
	mp2[t] = 1;
	for (long long i = 2, j; i <= x; i = j) {
		j = x / (x / i) + 1;
		solve(x / i);
		mp1[t] -= (j - i) * Phi(x / i);
		mp2[t] -= (j - i) * Mu(x / i);
	}
}

int main() {
	init();
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%lld", &n);
		memset(vis, false, sizeof vis);
		if (n < N) {
			printf("%lld %lld\n", phi[n], mu[n]);
		} else {
			solve(n);
			printf("%lld %lld\n", mp1[1], mp2[1]);
		}
	}
	return 0;
}