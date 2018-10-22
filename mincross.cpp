/*
Created 2018-10-21
"USACO 2017 February Contest, Platinum
Problem 1. Why Did the Cow Cross the Road"
A solution with BIT
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int bit[N];

int lowbit(int x) {
	return x & -x;
}

void add(int p) {
	for (; p < N; p += lowbit(p)) {
		bit[p]++;
	}
}

int sum(int p) {
	int ret = 0;
	for (; p; p -= lowbit(p)) {
		ret += bit[p];
	}
	return ret;
}

int n;
int breed[2][N];
int pos[2][N];
int ops[2][N];

long long intersect(int t) {
	long long ret = 0;
	for (int i = n; i >= 1; i--) {
		ret += sum(ops[t][i]);
		add(ops[t][i]);
	}
	return ret;
}

int main() {
	freopen("mincross.in", "r", stdin);
	freopen("mincross.out", "w", stdout);
	scanf("%d", &n);
	for (int t = 0; t < 2; t++) {
		for (int i = 1; i <= n; i++) {
			scanf("%d", &breed[t][i]);
			pos[t][breed[t][i]] = i;
		}
	}
	for (int t = 0; t < 2; t++) {
		for (int i = 1; i <= n; i++) {
			ops[t][i] = pos[t^1][breed[t][i]];
		}
	}
	long long ans = 1e18;
	for (int t = 0; t < 2; t++) {
		memset(bit, 0, sizeof bit);
		long long cnt = intersect(t);
		ans = min(ans, cnt);
		for (int i = n; i >= 1; i--) {
			cnt = cnt - (n - ops[t][i]) + (ops[t][i] - 1);
			ans = min(ans, cnt);
		}
	}
	printf("%lld\n", ans);
	return 0;
}