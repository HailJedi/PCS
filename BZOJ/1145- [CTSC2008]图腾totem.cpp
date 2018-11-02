#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 2e5+5;
const int P = 16777216;
int a[N];
int n;

int lowbit(int x) {
	return x & -x;
}

void add(ll *b, int p, int n, ll v) {
	for (; p <= n; p += lowbit(p)) {
		b[p] += v;
	}
}

ll ask(ll *b, int p) {
	ll ret = 0;
	for (; p > 0; p -= lowbit(p)) {
		ret += b[p];
	}
	return ret;
}

ll f1x2x() {
	return 0;
}

ll f14xx() {
	return 0;
}

ll f12xx() {
	return 0;
}

ll f1234() {
	return 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	ll ans = f1x2x() - f14xx() - f12xx() + f1234();
	cout << (ans % P + P) % P << endl;
	return 0;
}