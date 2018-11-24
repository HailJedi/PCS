/*
Created 2018-11-24
"Segments on the Line"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1500 + 5;
const int INF = 1e9 + 7;

int f[2][N];

struct Segment {
	int l, r;
	Segment() {}
	bool operator < (const Segment &sg) const {
		if (l != sg.l) {
			return l < sg.l;
		}
		return r > sg.r;
	}
} seg[N];

int n, m, s, k;
int a[N];
int sum[N];
int val[N];

bool check(int x) {
	for (int i = 1; i <= n; i++) {
		sum[i] = sum[i-1] + (a[i] <= x);
	}
	int t = 0;
	memset(f[t], 0, sizeof f[t]);
	for (int take = 1; take <= m; take++) {
		deque<int> q;
		t ^= 1;
		for (int i = 1, j = 1, best = 0; i <= s; i++) {
			while (seg[j].r < seg[i].l) {
				best = max(best, f[t^1][j]);
				if (!q.empty() && q.front() == j) {
					q.pop_front();
				}
				j++;
			}
			f[t][i] = best + sum[seg[i].r] - sum[seg[i].l-1];
			if (!q.empty()) {
				f[t][i] = max(f[t][i], sum[seg[i].r] + val[q.front()]);
			}
			val[i] = f[t^1][i] - sum[seg[i].r];
			while (!q.empty() && val[q.back()] <= val[i]) {
				q.pop_back();
			}
			q.push_back(i);
		}
	}
	return *max_element(f[t]+1, f[t]+1+s) >= k;
}

int main() {
	scanf("%d %d %d %d", &n, &s, &m, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= s; i++) {
		scanf("%d %d", &seg[i].l, &seg[i].r);
	}
	sort(seg+1, seg+1+s);
	int t = 1;
	for (int i = 2; i <= s; i++) {
		if (seg[i].r > seg[t].r) {
			seg[++t] = seg[i];
		}
	}
	s = t;
	int lp = 0, rp = INF;
	if (!check(INF)) {
		puts("-1");
	} else {
		while (rp - lp > 1) {
			int mid = (lp + rp) / 2;
			if (check(mid)) {
				rp = mid;
			} else {
				lp = mid;
			}
		}
		printf("%d\n", rp);
	}
	return 0;
}
