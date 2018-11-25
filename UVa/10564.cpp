#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int N = 100;
const int S = 1000;

int mat[N][N];
int f[N][N][S];
long long p[N][N][S];
string g[N][N][S];
int n;

int dp(int r, int c, int s) {
	if (f[r][c][s] != -1) {
		return f[r][c][s];
	}
	f[r][c][s] = 0;
	if (s < mat[r][c]) {
		return 0;
	}
	if (r == 2 * n - 1) {
		f[r][c][s] = p[r][c][s] = s == mat[r][c];
		return f[r][c][s];
	}
	int t = r < n;
	if (mat[r+1][c+(!t)] != -1 && dp(r+1, c+(!t), s-mat[r][c])) {
		f[r][c][s] = 1;
		g[r][c][s] = "R";
		p[r][c][s] = p[r+1][c+(!t)][s-mat[r][c]];
	}
	if (mat[r+1][c-t] != -1 && dp(r+1, c-t, s-mat[r][c])) {
		f[r][c][s] = 1;
		g[r][c][s] = "L";
		p[r][c][s] += p[r+1][c-t][s-mat[r][c]];
	}		
	return f[r][c][s];
}

string get_path(int c, int s) {
	int r = 1, ss = s;
	string ret = "";
	while (r != 2 * n - 1) {
		ret += g[r][c][s];
		ss -= mat[r][c];
		int t = r < n;
		c -= (g[r][c][s] == "L" && t);
		c += (g[r][c][s] == "R" && (!t));
		s = ss;
		r++;
	}
	return ret;
}
		

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	int s;
	while (cin >> n >> s && n + s) {
		memset(mat, -1, sizeof mat);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n-i+1; j++) {
				cin >> mat[i][j];
			}
		}
		for (int i = n+1; i <= 2*n-1; i++) {
			for (int j = 1; j <= i-n+1; j++) {
				cin >> mat[i][j];
			}
		}
		int ans = -1;
		memset(f, -1, sizeof f);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = 0; k < S; k++) {
					p[i][j][k] = 0;
				}
			}
		}
		long long pth = 0;
		for (int i = n; i >= 1; i--) {
			if (dp(1, i, s)) {
				ans = i;
				pth += p[1][i][s];
			}
		}
		cout << pth << endl;
		if (ans != -1) {
			cout << ans-1 << ' ' << get_path(ans, s);
		}
		cout << endl;
	}
	return 0;
}