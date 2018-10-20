/*
Created 2018-10-20
"USACO 2017 February Contest, Gold
Problem 3. Why Did the Cow Cross the Road III"
A counting problem with BIT solution 😂
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 50000 + 5;

int n;
int seq[2*N];
int l[N], r[N];

int bit[N*2];

int lowbit(int x) {
	return x & -x;
}

void add(int p, int v) {
	for (; p < 2*N; p += lowbit(p)) {
		bit[p] += v;
	}
}

int ask(int p) {
	int ret = 0;
	for (; p; p -= lowbit(p)) {
		ret += bit[p];
	}
	return ret;
}

int sum(int l, int r) {
	return ask(r) - ask(l);
}

int main() {
	freopen("circlecross.in", "r", stdin);
	freopen("circlecross.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= 2*n; i++) {
		scanf("%d", &seq[i]);
		if (l[seq[i]] == 0) {
			l[seq[i]] = i;
		} else {
			r[seq[i]] = i;
		}
	}
	int ans = 0;
	for (int i = 1; i <= 2*n; i++) {
		if (i == l[seq[i]]) {
			add(i, 1);
		} else {
			ans += sum(l[seq[i]], i);
			add(l[seq[i]], -1);
		}
	}
	printf("%d\n", ans);
	return 0;
}
