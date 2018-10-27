/*
Created 2018-10-27
"USACO 2012 February Contest, Gold Division
Problem 1. Cow Coupons"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 50000 + 5;

struct Cow {
	int p, c, id;
	Cow() {}
	bool operator < (const Cow &cow) const {
		return c < cow.c;
	}
} cow[N];

int n, k;
long long m;
bool inq[N];

bool cmp_c(Cow &c1, Cow &c2) {
	return c1.c < c2.c;
}

bool cmp_p(Cow &c1, Cow &c2) {
	return c1.p < c2.p;
}

int main() {
	freopen("coupons.in", "r", stdin);
	freopen("coupons.out", "w", stdout);
	scanf("%d %d %lld", &n, &k, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &cow[i].p, &cow[i].c);
		cow[i].id = i;
	}
	sort(cow+1, cow+1+n, cmp_c);
	priority_queue<Cow> q;
	for (int i = 1; i <= n; i++) {
		if (m >= cow[i].c && k > 0) {
			m -= cow[i].c;
			k--;
			q.push(cow[i]);
			inq[cow[i].id] = true;
		} else {
			break;
		}
	}
	int ans = q.size();
	if (ans == 0) {
		printf("%d\n", ans);
		return 0;
	}
	sort(cow+1, cow+1+n, cmp_p);
	for (int i = 1; i <= n; i++) {
		if (!inq[cow[i].id]) {
			if (m >= cow[i].p) {
				ans++;
				m -= cow[i].p;
			} else {
				if (m + q.top().c - q.top().p - cow[i].c >= 0) {
					m = m + q.top().c - q.top().p - cow[i].c;
					ans++;
				} else
				if (cow[i].p < q.top().c) {
					m = m + q.top().c - cow[i].p;
					q.pop();
				} else {
					break;
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
