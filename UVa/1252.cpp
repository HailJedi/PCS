#include <bits/stdc++.h>

using namespace std;

const int M = 11;
const int N = 128 + 5;

int f[1<<M][1<<M];
int cnt[1<<M][1<<M];
int feature[N];
int n, m;

int dp(int ask, int fea) {
	if (f[ask][fea] != -1) {
		return f[ask][fea];
	}
	if (cnt[ask][fea] == 1) {
		return f[ask][fea] = 0;
	}
	f[ask][fea] = m;
	for (int i = 0; i < m; i++) {
		if (!(ask & (1 << i))) {
			int ask2 = ask | (1 << i), fea2 = fea | (1 << i);
			if (cnt[ask2][fea] >= 1 && cnt[ask2][fea2] >= 1) {
				f[ask][fea] = min(f[ask][fea], max(dp(ask2, fea), dp(ask2, fea2)) + 1);
			}
		}
	}
	return f[ask][fea];
}

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	while (cin >> m >> n && m + n) {
		memset(feature, 0, sizeof feature);
		for (int i = 1; i <= n; i++) {
			string str;
			cin >> str;
			for (int j = 0; j < m; j++) {
				if (str[j] == '1') {
					feature[i] |= (1 << j);
				}
			}
		}
		memset(cnt, 0, sizeof cnt);
		for (int i = 0; i < (1 << m); i++) {
			for (int j = 1; j <= n; j++) {
				cnt[i][i & feature[j]]++;
			}
		}
		memset(f, -1, sizeof f);
		cout << dp(0, 0) << endl;
	}
	return 0;
}
