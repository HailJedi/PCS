#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int mod = 1e9+7;
const int N = 110;
int n, m;
string s;

struct matrix {
	ll x[N][N];
	matrix() { memset(x, 0, sizeof(x)); }
	const ll *operator[](int i) const { return x[i]; }
	ll *operator[](int i) { return x[i]; }
};

matrix operator*(const matrix &a, const matrix &b) {
	matrix c = matrix();
	for (int i = 0; i <= n; i++) 
		for (int j = 0; j <= n; j++)
			for (int k = 0; k <= n; k++) 
				(c[i][j] += a[i][k] * b[k][j]) %= mod;
	return c;
}

matrix dp[N];

void debug() {
	for (int i = 0; i <= m; i++) {
		cout << "matrix #" << i << endl;
		for (int k = 0; k <= n; k++) {
			for (int j = 0; j <= n; j++) 
				cout << dp[i][k][j] << ' ';
			puts("");
		}
	}
}

int main() {
	cin >> n >> m >> s;
	dp[0][0][0] = dp[0][n][n] = dp[1][0][0] = dp[1][n][n] = 2;
	for (int i = 1; i < n; i++) dp[0][i][i] = dp[1][i][i] = 1;
	for (int i = 0; i < n; i++) {
		if (s[i] == '0') dp[0][i][i+1] = 1;
		if (s[i] == '1') dp[1][i][i+1] = 1;[pop               ]
	}
	for (int i = 2; i <= m; i++) dp[i] = dp[i-1] * dp[i-2];
	debug();
	cout << dp[m][0][n] << endl;
	return 0;
}