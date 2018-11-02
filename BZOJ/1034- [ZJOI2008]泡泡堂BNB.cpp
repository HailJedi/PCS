#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;
int a[N], b[N];
int n, t;

int f(int *a, int *b, int l) {
	int ret = 0;
	for (int i = n-l; i < n; i++) {
		if (a[i] < b[i-n+l]) {
			return 0;
		} else {
			ret += (a[i] == b[i-n+l] ? 1 : 2);
		}
	}
	return ret;
}

int solve(int *a, int *b) {	
	int l = 0, r = n + 1;
	while (r - l > 4) {
		int len = r - l + 1;
		int m1 = l + len / 3 - 1;
		int m2 = r - len / 3 + 1;
		if (f(a, b, m1) < f(a, b, m2)) {
			l = m1;
		} else {
			r = m2;
		}
	}
	int res = -1;
	for (int i = l; i <= r; i++) {
		res = max(res, f(a, b, i));
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}	
	sort(a, a + n);
	sort(b, b + n);
	cout << solve(a, b) << ' ' << 2 * n - solve(b, a);
	return 0;
}