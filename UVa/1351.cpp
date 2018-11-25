#include <bits/stdc++.h>

using namespace std;

const int N = 200 + 5;

string str;
int f[N][N];

bool repeat(int l, int r, int t) {
	int len = r - l + 1, p = l;
	vector<string> comp;
	for (int i = 1; i <= len / t; i++) {
		comp.push_back(str.substr(p, t));
		p += t;
	}
	for (int i = 1; i < comp.size(); i++) {
		if (comp[i] != comp[i-1]) {
			return false;
		}
	}
	return true;
}

int digit(int x) {
	int ret = 0;
	while (x) {
		ret++;
		x /= 10;
	}
	return ret;
}

int dp(int l, int r) {
	if (f[l][r] != -1) {
		return f[l][r];
	}
	int len = r - l + 1;
	f[l][r] = len;
	for (int i = l; i < r; i++) {
		f[l][r] = min(f[l][r], dp(l, i) + dp(i+1, r));
	}
	for (int i = 1; i < len; i++) {
		if (len % i == 0 && repeat(l, r, i)) {
			f[l][r] = min(f[l][r], digit(len / i) + 2 + dp(l, l+i-1));
		}
	}
	return f[l][r];
}

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	int T;
	cin >> T;
	while (T--) {
		cin >> str;
		memset(f, -1, sizeof f);
		cout << dp(0, str.length()-1) << endl;
	}
	return 0;
}
