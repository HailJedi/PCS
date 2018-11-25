#include <bits/stdc++.h>

using namespace std;

const int N = 1e3+5;

int f[N][N];
string g[N][N];
string s;
int n;

void update(int i, int j, int cand, string scand) {
	if (cand > f[i][j]) {
		g[i][j] = scand;
		f[i][j] = cand;
	} else
	if (cand == f[i][j]) {
		if (g[i][j] == "") {
			g[i][j] = scand;
		} else {
			g[i][j] = min(g[i][j], scand);
		}
	}
}

void dp(int i, int j) {
	if (f[i][j] != -1) {
		return;
	}
	if (i == j) {
		g[i][j] = s.substr(i, j-i+1);
		f[i][j] = 1;
		return;
	}
	if (s[i] == s[j]) {
		dp(i+1, j-1);
		f[i][j] = f[i+1][j-1] + 2;
		g[i][j] = s[i] + g[i+1][j-1] + s[j];
	}
	dp(i, j-1);
	dp(i+1, j);
	update(i, j, f[i][j-1], g[i][j-1]);
	update(i, j, f[i+1][j], g[i+1][j]);
	return;
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	while (cin >> s) {
		n = s.length();
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++) {
				f[i][j] = -1;
				g[i][j] = "";
			}
		}
		dp(0, n-1);
		cout << g[0][n-1] << endl;
	}
	return 0;
}
				