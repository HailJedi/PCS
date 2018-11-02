#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, t, f, x, k;
	cin >> t;
	while (t--) {
		cin >> n;
		f = 1, k = 0;
		for (int i = 1; i <= n; i++) {
			cin >> x;
			if (x != 1) {
				f = 0;
			}
			k ^= x;
		}
		if (f) {
			if (n & 1) {
				cout << "Brother" << endl;
			} else {
				cout << "John" << endl;
			}
		} else {
			if (k != 0) {
				cout << "John" << endl;
			} else {
				cout << "Brother" << endl;
			}
		}
	}
	return 0;
}