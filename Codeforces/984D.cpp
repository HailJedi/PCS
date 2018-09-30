#include <bits/stdc++.h>

using namespace std;

const int N = 5e3+5;

int maxv[N][N], val[N][N];
int n, q, l, r;

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> val[i][1];
		maxv[i][1] = val[i][1];
	}
	for (int len = 2; len <= n; len++) 
		for (int i = 1; i + len <= n + 1; i++) {
			val[i][len] = val[i][len-1] ^ val[i+1][len-1];
			maxv[i][len] = max(val[i][len], max(maxv[i][len-1], maxv[i+1][len-1]));
		}
	cin >> q;
	while (q--) {
		cin >> l >> r;
		cout << maxv[l][r-l+1] << endl;
	}
	return 0;
}