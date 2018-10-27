/*
Created 2018-10-27
"USACO 2012 January Contest, Gold Division
Problem 2. Cow Run"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 15;

int n, m, k;
int a[8 * N];
char bsmv[N];

int calc(int d, int x, int fj, int bs) {
	return (1LL * x * a[8*d+4*fj+2*bs] + a[8*d+4*fj+2*bs+1] + x) % m;
}

bool solve_and(int d, int x, bool fj);
bool solve_or(int d, int x);

bool solve_and(int d, int x, bool fj) {
	bool bs = rand() & 1;
	return solve_or(d+1, calc(d, x, fj, bs)) && solve_or(d+1, calc(d, x, fj, !bs));
}

bool solve_or(int d, int x) {
	if (d == n) {
		return x <= k || x + k >= m;
	}
	bool fj = rand() & 1;
	return solve_and(d, x, fj) || solve_and(d, x, !fj);
}

int main() {
	freopen("cowrun.in", "r", stdin);
	freopen("cowrun.out", "w", stdout);
	scanf("%d %d %d", &n, &m, &k);
	scanf("%s", bsmv);
	for (int i = 0; i < 8 * n; i++) {
		scanf("%d", &a[i]);
	}
	int x = 0;
	for (int i = 0; i < n; i++) {
		if (solve_and(i, x, true)) {
			printf("B");
			x = calc(i, x, true, bsmv[i] == 'B');
		} else {
			printf("T");
			x = calc(i, x, false, bsmv[i] == 'B');
		}
	}
	puts("");
	return 0;
}
