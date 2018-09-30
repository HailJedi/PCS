#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll n, m, k;

int main() {
	cin >> n >> m >> k;
	if (k <= n-1) {
		cout << 1+k << ' ' << 1 << endl;
	} else {
		k -= (n-1);
		ll lev = k / (m-1);
		ll mov = k % (m-1);
		if (mov) {
			cout << n - lev << ' ';
			if (lev & 1) {
				cout << m - mov + 1 << endl;
			} else {
				cout << mov + 1 << endl;
			}
		} else {
			cout << n - lev + 1 << ' ';
			if (lev & 1) {
				cout << m << endl;
			} else {
				cout << 2 << endl;
			}
		}
	}
	return 0;
}