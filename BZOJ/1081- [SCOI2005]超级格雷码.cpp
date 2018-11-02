#include <bits/stdc++.h>

using namespace std;

const int N = 25;
int n, b;
int p[N];

void print(int x) {
	if (x < 10) {
		cout << x;
	} else {
		cout << char('A' + x - 10);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cout.tie(0);
	cin >> n >> b;
	p[0] = 1;
	for (int i = 1; i <= n; i++) {
		p[i] = p[i-1] * b;
	}
	for (int i = 0; i < p[n]; i++) {
		for (int j = n-1; j >= 0; j--) {
			int x = i / p[n-j], y = (i / p[n-j-1]) % b;
			if (x & 1) {
				print(b-y-1);
			} else {
				print(y);
			}
		}
		cout << endl;
	}
	return 0;
}