/*
Created 2018-12-11
"[JSOI2007]字符加密Cipher"
*/

#pragma C++ optimize(2)

#include <bits/stdc++.h>

using namespace std;

const int N = 200000 + 5;

int n;
char str[N];
int sa[N], rk[N];

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
			temp[i] = Triple(i, rk[i], i+k <= n ? rk[i+k] : 0);
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
	scanf("%s", str+1);
	n = strlen(str+1);
	for (int i = n+1; i <= 2*n; i++) {
		str[i] = str[i-n];
	}
	n *= 2;
	build();
	n /= 2;
	for (int i = 1; i <= 2*n; i++) {
		if (sa[i] <= n) {
			printf("%c", str[sa[i]+n-1]);
		}
	}
	puts("");
	return 0;
}