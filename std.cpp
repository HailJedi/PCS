#include <bits/stdc++.h>

using namespace std;

const int N = 41;

int n, ans;
string s;
int dp[N][2][N][N*N];
map<string, int> idx;
vector<string> v;
set<string> pref;

void add(int len, int have, int pre, int suf, char ch) {
	string cur = s.substr(0, pre);
	cur += ch;
	int nxtHave = have;
	while (!pref.count(cur)) {
		cur = cur.substr(1, cur.size()-1);
  }
	if (cur.size() == s.size()) {
		nxtHave = 1;
  }
	int nxtPre = cur.size();
	cur = v[suf];
	cur += ch;
	int nxtSuf = suf;
	if (cur.size() == len+1 && idx.count(cur)) {
		nxtSuf = idx[cur];
  }
	dp[len+1][nxtHave][nxtPre][nxtSuf] += dp[len][have][pre][suf];
}

void work(int len, int have, int pre, int suf) {
	if (!dp[len][have][pre][suf]) {
		return;
  }
	if (len == n) {
		if (have) {
			ans += dp[len][have][pre][suf];
			return;
		}
		string cur = v[pre] + v[suf];
		if (cur.find(s) != string::npos) {
			ans += dp[len][have][pre][suf];
    }
		return;
	}
	add(len, have, pre, suf, '0');
	add(len, have, pre, suf, '1');
}

int main() {
  freopen("read.in", "r", stdin);
	cin >> n >> s;
	idx[""] = 0;
	v.push_back("");
	pref.insert("");
	int sz = s.size();
	for (int i = 0; i < sz; i++) {
		string cur = "";
		for (int j = i; j < sz; j++) {
			cur += s[j];
			if (!idx.count(cur)) {
				int sz = idx.size();
				idx[cur] = sz;
				v.push_back(cur);
			}
			if (i == 0) {
				pref.insert(cur);
      }
		}
	}
	dp[0][0][0][0] = 1;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= 1; j++) {
			for (int k = 0; k <= n; k++) {
				for (int l = 0; l < v.size(); l++) {
					work(i, j, k, l);
        }
      }
    }
  }
	cout << ans << endl;
	return 0;
}
