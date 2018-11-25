#include <bits/stdc++.h>

using namespace std;

const int N = 1e2 + 5;
const int M = 1e4 + 5;

struct DS {
	deque< pair<int, int> > q;
	
	void append(int pos, int val) {
		while (!q.empty() && val > q.back().first) {
			q.pop_back();
		}
		q.push_back(make_pair(val, pos));
	}
	
	void erase(int pos) {
		while (!q.empty() && q.front().second <= pos) {
			q.pop_front();
		}
	}
	
	int max_val() {
		if (q.empty()) {
			return -1e9;
		}
		return q.front().first;
	}

	void clear() {
		while (!q.empty()) {
			q.pop_back();
		}
	}
} ds, ds2;

int f[2][M];
int hap, hs[N][M];
int len, ls[N][M];

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int n, m, k, t = 0;
	while (scanf("%d %d %d", &n, &m, &k) == 3 && n) {
		memset(f, 0, sizeof f);
		for (int i = 0; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				scanf("%d", &hap);
				hs[i][j] = hs[i][j-1] + hap;
			}
		}
		for (int i = 0; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				scanf("%d", &len);
				ls[i][j] = ls[i][j-1] + len;
			}
		}
		for (int i = 0; i <= n; i++) {	
			t ^= 1;
			ds.clear();
			ds2.clear();
			ds2.append(0, hs[i][0] + f[t^1][0]);
			int lp = 0, rp = 0;
			for (int j = 0; j <= m; j++) {
				while (ls[i][j] - ls[i][lp] > k) {
					ds.erase(lp);
					lp++;
				}
				while (rp+1 <= m && ls[i][rp+1] - ls[i][j] <= k) {
					rp++;
					ds2.append(rp, hs[i][rp] + f[t^1][rp]);
				}
				f[t][j] = max(hs[i][j] + ds.max_val(), ds2.max_val() - hs[i][j]);
				ds.append(j, - hs[i][j] + f[t^1][j]);
				ds2.erase(j);
			}
		}
		printf("%d\n", *max_element(f[t], f[t]+m+1));
	}
	return 0;
}