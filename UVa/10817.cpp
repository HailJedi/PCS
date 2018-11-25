#include <bits/stdc++.h>

using namespace std;

const int S = 8;
const int N = 100+5;
const int INF = 1e9;

int f[N][1<<S][1<<S];
int cnt[S], cost[N], teach[N];
int s, m, n;

int dp(int cur, int todo, int done) {
	int &ret = f[cur][todo][done];
	if (ret != -1) {
		return ret;
	}
	if (done == (1 << s) - 1) {
		return ret = 0;
	}
	if (cur == n + 1) {
		return ret = INF;
	}
	ret = min(INF, dp(cur+1, todo, done));
	int zero = (~todo) & teach[cur], one = todo & teach[cur];
	ret = min(ret, dp(cur+1, todo ^ one | zero, done | one) + cost[cur]);
	return ret;
}

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("test.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	string str;
	while (getline(cin, str)) {
		stringstream in(str);
		in >> s >> m >> n;
		if (s == 0) {
			break;
		}
		int c, ans = 0;
		string str;
		memset(cnt, 0, sizeof cnt);
		for (int i = 1; i <= m; i++) {
			getline(cin, str);
			stringstream in(str);
			in >> c;
			ans += c;
			while (in >> c) {
				cnt[c-1]++;
			}
		}
		memset(teach, 0, sizeof teach);
		for (int i = 1; i <= n; i++) {
			getline(cin, str);
			stringstream in(str);
			in >> cost[i];
			while (in >> c) {
				teach[i] |= (1 << (c-1));
			}
		}
		int done = 0, todo = 0;
		for (int i = 0; i < s; i++) {
			if (cnt[i] >= 2) {
				done |= (1 << i);
			} else {
				todo |= (cnt[i] << i);
			}
		}
		memset(f, -1, sizeof f);
		cout << ans + dp(1, todo, done) << endl;
	}
	return 0;
}
