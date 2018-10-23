/*
Created 2018-10-23
"Getting Deals Done"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 200000 + 5;

int n, T, m;
long long t;
pair<int, int> p[N];

long long num[N], cost[N];

int lowbit(int x) {
	return x & -x;
}

void add(long long *bit, int p, int v) {
	for (; p <= n; p += lowbit(p)) {
		bit[p] += v;
	}
}

long long ask(long long *bit, int p) {
	long long ret = 0;
	for (; p; p -= lowbit(p)) {
		ret += bit[p];
	}
	return ret;
}

int pos(int i) {
	int l = -1, r = n+1;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		if (ask(num, mid) >= i) {
			r = mid;
		} else {
			l = mid;
		}
	}
	return r;
}

int solve(int i) {
	int l = 0, r = i / m + 1;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		if (2 * ask(cost, pos(mid * m)) <= t) {
			l = mid;
		} else {
			r = mid;
		}
	}
	long long rest = t - 2 * ask(cost, pos(l * m));
	int old_l = l * m, old_pos = pos(old_l);
	l = old_l, r = min(i+1, old_l+m+1);
	while (r - l > 1) {
		int mid = (l + r) / 2;
		if (ask(cost, pos(mid)) - ask(cost, old_pos) <= rest) {
			l = mid;
		} else {
			r = mid;
		}
	}
	return l;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %lld", &n, &m, &t);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &p[i].first);
			p[i].second = i;
		}
		sort(p+1, p+1+n);
		int d = -1, job = -1;
		for (int i = 1; i <= n; i++) {
			num[i] = cost[i] = 0;
		}
		for (int i = 1; i <= n; i++) {
			add(cost, p[i].second, p[i].first);
			add(num, p[i].second, 1);
			if (i < n && p[i].first == p[i+1].first) {
				continue;
			}
			int done = solve(i);
			if (d == -1 || done > job) {
				d = p[i].first;
				job = done;
			}
		}
		printf("%d %lld\n", job, min(t, 1LL * d));
	}
	return 0;
}
