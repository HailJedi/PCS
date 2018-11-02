#include <bits/stdc++.h>

using namespace std;

const int N = 50+5;
char s[N];
int f[N][N][2];

bool same(int l, int r) {
	int len = r - l + 1;
	if (len & 1) {
		return false;
	}
	for (int i = l; i <= (l + r) / 2; i++) {
		if (s[i] != s[i + len / 2]) {
			return false;
		}
	}
	return true;
}

int dp(int l, int r, int b) {
	if (l == r) {
		return 1;
	}
	int &ret = f[l][r][b];
	if (ret != -1) {
		return ret;
	}
	ret = 2e9;
	for (int i = l; i < r; i++) {
		if (b) {
			ret = min(ret, dp(l, i, 1) + dp(i + 1, r, 1) + 1);
		}
		ret = min(ret, dp(l, i, b) +  r - i);
	}
	if (same(l, r)) {
		ret = min(ret, dp(l, (l + r) / 2, 0) + 1);
	}
	return ret;
}

int main() {
	scanf("%s", s + 1);
	int l = strlen(s + 1);
	for (int i = 1; i <= l; i++) {
		for (int j = 1; j <= l; j++) {
			f[i][j][0] = f[i][j][1] = -1;
		}
	}
	cout << dp(1, l, 1) << endl;
	return 0;
}