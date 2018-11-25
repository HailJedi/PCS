#include <bits/stdc++.h>

using namespace std;

const int L = 20 + 5;
const int N = 100 + 5;
const int S = 2 * N * L;
const long long INF = 1e18;

map<string, int> str2id[L];
vector<string> id2str[L];

void add_suffix(string suf) {
	int len = suf.length();
	if (!str2id[len].count(suf)) {
		str2id[len][suf] = id2str[len].size();
		id2str[len].push_back(suf);
	}
}

long long dis[S][S], preDis[S][S];
set< pair<string, string> > rule;

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	string s, t;
	int n, kase = 0;
	while (cin >> s >> t >> n && s != ".") {
		int slen = s.length();
		rule.clear();
		for (int i = 0; i < L; i++) {
			str2id[i].clear();
			id2str[i].clear();
		}
		for (int i = 0; i < slen; i++) {
			add_suffix(s.substr(i));
			add_suffix(t.substr(i));
		}
		for (int i = 1; i <= n; i++) {
			string a, b;
			cin >> a >> b;
			rule.insert(make_pair(a, b));
			for (int j = 0; j < a.length(); j++) {
				add_suffix(a.substr(j));
				add_suffix(b.substr(j));
			}
		}
		for (int len = 1; len <= slen; len++) {
			int idn = id2str[len].size();
			for (int i = 0; i < idn; i++) {
				for (int j = 0; j < idn; j++) {
					dis[i][j] = INF;
				}
				dis[i][i] = 0;
			}
			for (int i = 0; i < idn; i++) {
				for (int j = 0; j < idn; j++) {
					string str1 = id2str[len][i], str2 = id2str[len][j];
					if (i != j && rule.count(make_pair(str1, str2))) {
						dis[i][j] = 1;
					}
					if (i != j && len > 1 && str1[0] == str2[0]) {
						int p = str2id[len-1][str1.substr(1)], q = str2id[len-1][str2.substr(1)];
						dis[i][j] = min(dis[i][j], preDis[p][q]);
					}
				}
			}
			for (int k = 0; k < idn; k++) {
				for (int i = 0; i < idn; i++) {
					for (int j = 0; j < idn; j++) {
						preDis[i][j] = dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
					}
				}
			}
		}
		int st = str2id[slen][s], ed = str2id[slen][t];
		long long ans = dis[st][ed];
		cout << "Case " << ++kase << ": ";
		if (ans < INF) {
			cout << ans << endl;
		} else {
			cout << "No solution" << endl;
		}
	}
	return 0;
}
