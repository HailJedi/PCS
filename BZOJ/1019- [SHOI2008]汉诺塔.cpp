#include <bits/stdc++.h>

using namespace std;

const int N = 40;
int n;
string s;
long long g[3][N], f[3][N];

int main() {
	cin >> n;
	g[0][1] = g[1][1] = g[2][1] = -1;
	for (int i = 0; i < 6; i++) {
		cin >> s;
		int a = s[0] - 'A', b = s[1] - 'A';
		if (g[a][1] != -1) {
			continue;
		}
		g[a][1] = b;
		f[a][1] = 1;
	}
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j < 3; j++) {
			int a = g[j][i-1], b = 3 - j - a;
			if (g[a][i-1] == b) {
				f[j][i] = f[j][i-1] + 1 + f[a][i-1];
				g[j][i] = b;
			} else {
				f[j][i] = f[j][i-1] + 1 + f[a][i-1] + 1 + f[j][i-1];
				g[j][i] = a;
			}
		}
	}
	cout << f[0][n] << endl;

	return 0;
}