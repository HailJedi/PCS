/*
Created 2018-12-20
"cerc2008 Suffix reconstruction"
*/

#pragma C++ optimize(2)

#include <bits/stdc++.h>

using namespace std;

const int N = 500000 + 5;

int n;
int sa[N], rk[N];
char str[N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &sa[i]);
		rk[sa[i]] = i;
	}
	char cur = 'z';
	str[sa[n]] = cur;
	for (int i = n-1; i >= 1; i--) {
		int p1 = sa[i]+1, p2 = sa[i+1]+1;
		if (rk[p1] < rk[p2]) {
			str[sa[i]] = cur;
		} else {
			str[sa[i]] = --cur;
		}
	}
	if (cur < 'a') {
		puts("-1");
	} else {
		for (int i = 1; i <= n; i++) {
			printf("%c", str[i]);
		}
		puts("");
	}
	return 0;
}