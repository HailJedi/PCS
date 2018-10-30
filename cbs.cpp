/*
Created 2018-10-29
"USACO 2012 November Contest, Gold
Problem 2. Concurrently Balanced Strings"
*/

#include <bits/stdc++.h>

using namespace std;

const int K = 10 + 5;
const int N = 50000 + 5;

int n, k;
char par[K][N];
int lst_pos[K][2*N];

int main() {
	freopen("cbs.in", "r", stdin);
	freopen("cbs.out", "w", stdout);
	scanf("%d %d", &k, &n);
	for (int i = 0; i < k; i++) {
		scanf("%s", par[i]);
	}
	vector<vector<int>> lst_pos(k, vector<int>(2*n, n));
	map<vector<int>, pair<int, int>> st;
	vector<int> sum(k, n);
	for (int i = 0; i < k; i++) {
		lst_pos[i][n] = 0;
	}
	st[sum] = make_pair(0, 1);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int pt = 0;
		for (int j = 0; j < k; j++) {
			if (par[j][i] == '(') {
				lst_pos[j][++sum[j]] = i+1;
			} else {
				sum[j]--;
				lst_pos[j][sum[j]] = min(lst_pos[j][sum[j]], i+1);
			}
			pt = max(pt, lst_pos[j][sum[j]]);
		}
		pair<int, int> &lst = st[sum];
		if (lst.first == pt) {
			ans += lst.second++;
		} else {
			lst = make_pair(pt, 1);
		}
	}
	printf("%d\n", ans);
	return 0;
}
