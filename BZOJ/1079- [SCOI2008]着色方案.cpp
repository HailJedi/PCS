#include <bits/stdc++.h>

using namespace std;

const int N = 16;
const int M = 55556;
const int P = 1e9+7;
int k, t;
int ct[6];
long long f[N][N][N][N][N][6];

long long dp(int c1, int c2, int c3, int c4, int c5, int lst) {
	long long &ret = f[c1][c2][c3][c4][c5][lst];
	if (c1 + c2 + c3 + c4 + c5 == 0) {
		ret = 1;
	}
	if (ret != 0) {
		return ret;
	}
	if (c1) {
		(ret += (c1 - (lst == 2)) * dp(c1-1, c2, c3, c4, c5, 1)) %= P;
	}
	if (c2) {
		(ret += (c2 - (lst == 3)) * dp(c1+1, c2-1, c3, c4, c5, 2)) %= P;
	}
	if (c3) {
		(ret += (c3 - (lst == 4)) * dp(c1, c2+1, c3-1, c4, c5, 3)) %= P;
	}
	if (c4) {
		(ret += (c4 - (lst == 5)) * dp(c1, c2, c3+1, c4-1, c5, 4)) %= P;
	}
	if (c5) {
		(ret += (c5 - (lst == 6)) * dp(c1, c2, c3, c4+1, c5-1, 5)) %= P;
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> k;
	for (int i = 1; i <= k; i++) {
		cin >> t;
		ct[t]++;
	}
	cout << dp(ct[1], ct[2], ct[3], ct[4], ct[5], 0) % P << endl;
	return 0;
}