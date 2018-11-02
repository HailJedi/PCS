#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;
int k[N];
int n;

bool check() {
	for (int i = 1; i < n; i++) {
		if (k[i] == 0 && k[i-1] != 1 && k[i-1] != 3) {
			return false;
		}
	}
	return true;
}

int mx;

bool handle() {
	while (n > 1) {
		mx = max(mx, *max_element(k, k+n));
		if (!check()) {
			return false;
		}
		if (k[0] == 0) {
			k[0] = 2;
		}
		if (k[n-1] == 1) {
			n--;
		} else
		if (k[n-1] == 3) {
			k[n-1] = 2;
		}
		for (int i = 1; i < n; i++) {
			if (k[i] == 0) {
				if (k[i-1] == 1) {
					k[i-1] = 2, k[i] = -1;
				} else
				if (k[i-1] == 3) {
					k[i-1] = 2, k[i] = 2;
				}
			}
		}
		n = remove(k, k+n, -1) - k;
		for (int i = 0; i < n; i++) {
			k[i]--;
		}
	}
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> k[i];
		}
		mx = 0;
		if (handle()) {
			cout << "TAK" << endl;
		} else {
			cout << "NIE" << endl;
		}
		cout << mx << endl;
	}
	return 0;
}