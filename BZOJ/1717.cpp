/*
Created 2018-12-12
"[Usaco2006 Dec]Milk Patterns 产奶的模式"
*/

#pragma C++ optimize(2)

#include <bits/stdc++.h>

using namespace std;

const int N = 20000 + 5;

int n, k;
int str[N];

struct MonoQ {
	deque<int> q;
	void push(int v) {
		while (!q.empty() && v < q.back()) {
			q.pop_back();
		}
		q.push_back(v);
	}

	void pop(int v) {
		if (!q.empty() && v == q.front()) {
			q.pop_front();
		}
	}

	int min_val() {
		return q.front();
	}
} q;

struct Triple {
	int id, x, y;
	Triple() {}
	Triple(int id, int x, int y) : id(id), x(x), y(y) {}
	bool operator < (const Triple &tr) const {
		return x != tr.x ? x < tr.x : y < tr.y;
	}
} temp[N];

bool cmp(int i, int j) {
	return str[i] < str[j];
}

int sa[N], rk[N*2], ht[N];

void build() {
	for (int i = 1; i <= n; i++) {
		sa[i] = i;
	}
	sort(sa+1, sa+1+n, cmp);
	for (int i = 1; i <= n; i++) {
		rk[sa[i]] = rk[sa[i-1]] + (str[sa[i-1]] != str[sa[i]]);
	}
	for (int k = 1; k <= n; k *= 2) {
		for (int i = 1; i <= n; i++) {
			temp[i] = Triple(i, rk[i], rk[i+k]);
		}
		sort(temp+1, temp+1+n);
		for (int i = 1; i <= n; i++) {
			rk[temp[i].id] = rk[temp[i-1].id] + !(temp[i].x == temp[i-1].x && temp[i].y == temp[i-1].y);
		}
	}
	for (int i = 1; i <= n; i++) {
		sa[rk[i]] = i;
	}
	for (int i = 1, k = 0; i <= n; i++) {
		k -= k ? 1 : 0;
		int j = sa[rk[i]-1];
		while (str[j+k] == str[i+k]) {
			k++;
		}
		ht[rk[i]] = k;
	}
}

int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &str[i]);
	}
	build();
	int lp = 2, rp = 2;
	while (rp <= k) {
		q.push(ht[rp++]);
	}
	int ans = q.min_val();
	while (rp <= n) {
		q.pop(ht[lp++]);
		q.push(ht[rp++]);
		ans = max(ans, q.min_val());
	}
	printf("%d\n", ans);
	return 0;
}