#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;
int dat[N], lst[N];
int n, x;

int lowbit(int x) {
	return x & (-x);
}

void add(int p, int x) {
	for (int i = p; i <= 2*n; i += lowbit(i)) {
		dat[i] += x;
	}
}

int ask(int p) {
	int ret = 0;
	for (int i = p; i > 0; i -= lowbit(i)) {
		ret += dat[i];
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	long long ans = 0;
	cin >> n;
	for (int i = 1; i <= 2*n; i++) {
		cin >> x;
		if (!lst[x]) {
			lst[x] = i;
			add(i, 1);
		} else {
			ans += ask(i) - ask(lst[x]);
			add(lst[x], -1);
		}
	}
	cout << ans << endl;
	return 0;
}