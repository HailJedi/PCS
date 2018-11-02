#include <bits/stdc++.h>

using namespace std;

const int M = 55;
const int N = 1005;
int own[M], far[N], sum[N], sown;
int m, n, mid;

bool dfs(int cur, int lim, int thr) {
	if (thr + sum[lim] > sown) {
		return false;
	}
	if (cur == 0) {
		return true;
	}
	for (int i = 1; i <= m; i++) {
		if (own[i] >= far[cur]) {
			own[i] -= far[cur];
			if (dfs(cur-1, lim, thr + (own[i] < far[1] ? own[i] : 0))) {
				own[i] += far[cur];
				return true;
			}
			own[i] += far[cur];
		}
	}
	return false;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> m;
	for (int i = 1; i <= m; i++) {
		cin >> own[i];
		sown += own[i];
	}
	sort(own+1, own+1+m);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> far[i];
	}
	sort(far+1, far+1+n);
	for (int i = 1; i <= n; i++) {
		sum[i] = sum[i-1] + far[i];
	}
	int l = 0, r = n + 1;
	while (r - l >= 2) {
		int mid = (l + r) >> 1;
		if (dfs(mid, mid, 0)) {
			l = mid;
		} else {
			r = mid;
		}
	}
	cout << l << endl;
	return 0;
}