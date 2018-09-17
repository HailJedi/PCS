#include <bits/stdc++.h>

using namespace std;

int main() {
	long long n;
	cin >> n;
	n++;
	if (n & 1ll) cout << (n == 1 ? 0 : n) << endl;
	else cout << n / 2 << endl;
	return 0;
}