#include <bits/stdc++.h>

using namespace std;

const int N = 16;

long long INF = 1e18;
long long f[1<<N];
int can[N];
int n;

long long dp(int s, int w) {
	if (f[s] != -1) {
		return f[s];
	}
	f[s] = 0;
	for (int i = 0; i < n; i++) {
		if (!(s & (1 << i)) && w & (1 << i)) {
			f[s] += dp(s | (1 << i), w | can[i]);
		}
	}
	return f[s];
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0); 

	int T, kase = 0;
	cin >> T;
	while (T--) {
		cin >> n;
		memset(can, 0, sizeof can);
		char chr;
		int start = 0;
		for (int i = 0; i < n; i++) {
			cin >> chr;
			start |= ((chr == '1') << i);
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				char chr;
				cin >> chr;
				can[i] |= ((chr == '1') << j);
			}
		}
		memset(f, -1, sizeof f);
		f[(1<<n)-1] = 1;
		cout << "Case " << ++kase << ": " << dp(0, start) << endl;
	}
	return 0;
}
					