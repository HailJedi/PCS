/*
Created 2018-10-29
"USACO 2012 US Open, Gold Division
Problem 3. Balanced Cow Subsets"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 20;

long long m[N];
long long sum[1<<N];
bool taken[1<<N];
map<long long, vector<int>> data;
int hb[1<<N];

int main() {
	freopen("subsets.in", "r", stdin);
	freopen("subsets.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &m[i]);
		for (int j = 1; j < (1 << n); j++) {
			if (j & (1 << i)) {
				sum[j] += m[i];
			}
		}
	}
	for (int i = (1 << n) - 1; i; i--) {
		data[sum[i]].push_back(i);
		for (int j = n; j >= 0; j--) {
			if (i & (1 << j)) {
				hb[i] = j;
				break;
			}
		}
	}
	int ans = 0;
	int all = (1 << n) - 1;
	long long O = 0;
	for (auto e: data) {
		int sz = e.second.size();
		int rp = sz;
		for (int i = 0; i < sz; i++) {
			int rest = all ^ e.second[i];
			while (rp-1 > i && e.second[rp-1] <= rest) {
				rp--;
			}
			rp = max(rp, i+1);
			int lp = rp-1, rp = sz;
			while (rp - lp > 1) {
				int mid = (lp + rp) / 2;
				if (hb[e.second[mid]] == hb[e.second[i]]) {
					lp = mid;
				} else {
					rp = mid;
				}
			}
			rp = lp + 1;
			O += sz - rp;
			for (int j = rp; j < sz; j++) {
				if ((e.second[i] & e.second[j]) == 0) {
					ans += !taken[e.second[i] | e.second[j]];
					taken[e.second[i] | e.second[j]] = true;
				}
			}
		}
	}
	cout << O << endl;
	printf("%d\n", ans);
	return 0;
}

