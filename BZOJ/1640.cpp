/*
Created 2018-12-12
"[Usaco2007 Nov]Best Cow Line 队列变换"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 4000 + 5;

int n;
char str[N];
int sa[N], rk[N], rk2[N];

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
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> str[i];
		str[2*n+1-i] = str[i];
	}
	n *= 2;
	build();
	n /= 2;
	for (int i = n+1; i <= 2*n; i++) {
		rk2[2*n+1-i] = rk[i];
	}
	int lp = 1, rp = n, cnt = 0;
	while (lp <= rp) {
		if (rk[lp] < rk2[rp]) {
			cout << str[lp++];
		} else {
			cout << str[rp--];
		}
		cnt++;
		if (cnt % 80 == 0) {
			cout << endl;
		}
	}
	return 0;
}