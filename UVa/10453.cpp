#include <bits/stdc++.h>

using namespace std;

const int N = 1e3+5;
const int INF = 1e9;

int f[N][N];
string s;

int dp(int l, int r) {
	if (f[l][r] != -1) {
		return f[l][r];
	}
	if (l > r) {
		return f[l][r] = 0;
	}
	if (s[l] == s[r]) {
		f[l][r] = dp(l+1, r-1);
	} else {
		f[l][r] = min(dp(l+1, r), dp(l, r-1)) + 1;
	}
	return f[l][r];
}

void print(int l, int r) {
	if (l > r) {
		return;
	}
	if (l == r) {
		cout << s[l];
	} else
	if (s[l] == s[r] && f[l+1][r-1] != -1 && f[l][r] == f[l+1][r-1]) {
		cout << s[l];
		print(l+1, r-1);
		cout << s[r];
	} else
	if (f[l+1][r] != -1 && f[l][r] == f[l+1][r] + 1) {
		cout << s[l];
		print(l+1, r);
		cout << s[l];
	} else
	if (f[l][r-1] != -1 && f[l][r] == f[l][r-1] + 1) {
		cout << s[r];
		print(l, r-1);
		cout << s[r];
	}
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	while (cin >> s) {
		int n = s.length();
		memset(f, -1, sizeof f);
		for (int i = 0; i < n; i++) {
			f[i][i] = 0;
		}
		cout << dp(0, n-1) << ' ';
		print(0, n-1);
		cout << endl;
	}
	return 0;
}