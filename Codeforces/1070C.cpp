/*
Created 2018-10-23
"Cloud Computing"
A greedy solution with binary search + BIT
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;
const int M = 200000 + 5;

int n, k, m;
vector<int> day[N];
int l[M], r[M], p[M], c[M];

long long num[N];
long long cost[N];

int lowbit(int x) {
	return x & -x;
}

void add(long long *bit, int p, long long v) {
	for (; p < N; p += lowbit(p)) {
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

int main() {
	scanf("%d %d %d", &n, &k, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d %d", &l[i], &r[i], &c[i], &p[i]);
		day[l[i]].push_back(i);
		day[r[i]+1].push_back(i);
	}
	long long ans = 0, pre = 0;
	for (int d = 1; d <= n; d++) {
		if (!day[d].empty()) {
			for (int i: day[d]) {
				if (d == l[i]) {
					add(num, p[i], c[i]);
					add(cost, p[i], 1LL * p[i] * c[i]);
				} else {
					add(num, p[i], -c[i]);
					add(cost, p[i], -1LL * p[i] * c[i]);
				}
			}
			if (ask(num, N-1) < k) {
				pre = ask(cost, N-1);
			} else {
				int r = N-1, l = 0;
				while (r - l > 1) {
					int mid = (l + r) / 2;
					if (ask(num, mid) >= k) {
						r = mid;
					} else {
						l = mid;
					}
				}
				pre = ask(cost, r);
				long long cnt = ask(num, r);
				if (cnt > k) {
					pre -= r * (cnt - k);
				}
			}
		}
		ans += pre;
	}
	printf("%lld\n", ans);
	return 0;
}
