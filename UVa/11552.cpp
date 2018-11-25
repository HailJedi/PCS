#include <bits/stdc++.h>

using namespace std;

#define FOR(it, i) for (it = chr[i].begin(); it != chr[i].end(); ++it)

const int N = 1e3+5;
const int INF = 0x3f3f3f3f;

int f[N][26];
set<int> chr[N];

int dp(int idx, int lst) {
	if (f[idx][lst] != INF) {
		return f[idx][lst];
	}
	f[idx][lst] = chr[idx].size();
	int t = INF;
	set<int>::iterator it;
	FOR (it, idx-1) {
		if (chr[idx].count(*it) && (chr[idx].size() == 1 || (chr[idx].size() != 1 && lst != *it))) {
			t = min(t, dp(idx-1, *it) - 1);
		} else {
			t = min(t, dp(idx-1, *it));
		}
	}	
	return f[idx][lst] += t;
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int T;
	cin >> T;
	while (T--) {
		int k;
		string s;
		cin >> k >> s;
		int n = 1;
		while (chr[n].size()) {
			chr[n++].clear();
		}
		n = 1;
		for (int i = 0; i < s.length(); i++) {
			chr[n].insert(s[i] - 'a');
			n += (i % k == k - 1);
		}
		n--;
		memset(f, INF, sizeof f);
		set<int>::iterator it;
		FOR (it, 1) {
			f[1][*it] = chr[1].size();
		}
		int ans = INF;
		FOR (it, n) {
			ans = min(ans, dp(n, *it));
		}
		cout << ans << endl;
	}
	return 0;
}
		