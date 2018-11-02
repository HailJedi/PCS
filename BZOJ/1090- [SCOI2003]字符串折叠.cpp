#include <bits/stdc++.h>

using namespace std;

const int N = 105;
string s;
int f[N][N];

bool good(int l, int r, int i) {
	if ((r-l+1) % (i-l+1) != 0) {
		return false;
	}
	int len = i-l+1;
	for (int j = l; j <= i; j++) {
		for (int k = 1; j+len*k <= r; k++) {
			if (s[j+len*k] != s[j]) {
				return false;
			}
		}
	}
	return true;
}

int dig(int x) {
	int ret = 0;
	while (x) {
		x /= 10;
		ret++;
	}
	return ret;
}

int dp(int l, int r) {
	if (l == r) {
		return 1;
	}
	if (f[l][r] != -1) {
		return f[l][r];
	}
	f[l][r] = r - l + 1;
	for (int i = l; i < r; i++) {
		f[l][r] = min(f[l][r], dp(l, i) + dp(i+1, r));
		if (good(l, r, i)) {
			f[l][r] = min(f[l][r], dp(l, i) + 2 + dig((r-i)/(i-l+1)+1));
		}
	}
	return f[l][r];
}

int main() {
	cin >> s;
	memset(f, -1, sizeof(f));
	cout << dp(0, s.length()-1) << endl;
	return 0;
}