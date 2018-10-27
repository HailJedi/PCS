/*
Created 2018-10-25
"USACO 2011 November Contest, Gold Division
Problem 1. Above the Median"
😣
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int bit[2*N];

int lowbit(int x) {
	return x & -x;
}

void add(int p) {
	for (p += N; p < 2 * N; p += lowbit(p)) {
		bit[p]++;
	}
}

int ask(int p) {
	int ret = 0;
	for (p += N; p; p -= lowbit(p)) {
		ret += bit[p];
	}
	return ret;
}

int n, x;
int h[N];

int main() {
	freopen("median.in", "r", stdin);
	freopen("median.out", "w", stdout);
	scanf("%d %d", &n, &x);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &h[i]);
		h[i] = h[i] < x ? -1 : 1;
	}
	add(0);
	long long ans = 0, sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += h[i];
		ans += ask(sum);
		add(sum);
	}
	printf("%lld\n", ans);
	return 0;
}
