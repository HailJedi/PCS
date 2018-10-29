/*
Created 2018-10-29
"USACO 2012 March Contest, Gold Division
Problem 3. Cows in a Skyscraper"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 18;

int f[1<<N];
int wt[1<<N];
int pre[1<<N];
int w[N];

bool update(int &x, int y) {
	if (x == -1 || x > y) {
		x = y;
		return true;
	}
	return false;
}

int main() {
	freopen("skyscraper.in", "r", stdin);
// freopen("skyscraper.out", "w", stdout);
	int n, W;
	scanf("%d %d", &n, &W);
	int all = (1 << n) - 1;
	for (int i = 0; i < n; i++) {
		scanf("%d", &w[i]);
		for (int j = 1; j <= all; j++) {
			if (j & (1 << i)) {
				wt[j] += w[i];
			}
		}
	}
	memset(f, -1, sizeof f);
	f[0] = 0;
	for (int i = 0; i <= all; i++) {
		int rest = all ^ i;
		for (int j = rest; j; j = rest & (j-1)) {
			if (wt[j] <= W && update(f[i | j], f[i] + 1)) {
				pre[i|j] = i;
			}
		}
	}
	vector<int> ans;
	for (int st = all; st; st = pre[st]) {
		ans.push_back(st ^ pre[st]);
	}
	printf("%d\n", (int)ans.size());
	for (int st: ans) {
		printf("%d ", (int)__builtin_popcount(st));
		for (int i = 0; i < n; i++) {
			if (st & (1 << i)) {
				printf("%d ", i+1);
			}
		}
		puts("");
	}
	return 0;
}
		

