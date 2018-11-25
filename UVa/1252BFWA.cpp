#include <bits/stdc++.h>

using namespace std;

const int N = 128 + 5;
const int M = 11;

int v[N];
int cnt[1<<M];

int main() {
	freopen("read.in", "r", stdin);
	freopen("write.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	int m, n;
	while (cin >> m >> n && m + n) {
		for (int i = 1; i <= n; i++) {
			string str;
			cin >> str;
			v[i] = 0;
			for (int j = 0; j < m; j++) {
				if (str[j] == '1') {
					v[i] |= (1 << j);
				}
			}
		}
		int ans = m;
		memset(cnt, -1, sizeof cnt);
		for (int i = 0; i < (1 << m); i++) {
			if (__builtin_popcount(i) >= ans) {
				continue;
			}
			bool ok = true;
			for (int j = 1; j <= n; j++) {
				if (cnt[v[j] & i] == i) {
					ok = false;
					break;
				}
				cnt[v[j] & i] = i;
			}
			if (ok) {
				ans = min(ans, __builtin_popcount(i));
			}
		}
		cout << ans << endl;
	}
	return 0;
}
