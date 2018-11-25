#include <bits/stdc++.h>

using namespace std;

const int N = 16;

int con[N];
bool cov[1<<N];
int f[1<<N];

int dp(int s) {
	if (f[s] != -1) {
		return f[s];
	}
	f[s] = 0;
	if (!cov[s]) {
		return 0;
	}
	for (int t = s; t; t = s & (t-1)) {
		if (cov[t]) {
			f[s] = max(f[s], 1 + dp(s ^ t));
		}
	}
	return f[s];
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int n, kase = 0;
	while (cin >> n && n) {
		memset(con, 0, sizeof con);
		memset(cov, false, sizeof cov);

		int whole = (1 << n) - 1;	

		for (int i = 0; i < n; i++) {
			con[i] |= (1 << i);
			int m;
			cin >> m;
			for (int j = 0; j < m; j++) {
				int k;
				cin >> k;
				con[i] |= (1 << k);
			}
		}
		
		for (int i = 0; i <= whole; i++) {
			int s = 0; 
			for (int j = 0; j < n; j++) {
				if (i & (1 << j)) {
					s |= con[j];
				}
			}
			cov[i] = s == (whole);
		}

		memset(f, -1, sizeof f);
		cout << "Case " << ++kase << ": " << dp(whole) << endl;
	}
	
	return 0;
}