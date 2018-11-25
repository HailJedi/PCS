#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 5;
const int L = 20 + 5;
const int S = N + N*L;

string f[S][L];
int car[S], cdr[S];
bool vis[S];

vector< pair<int, int> > trans[S];

int ct;
string val[S];
map<string, int> id;

int ID(string s) {
	if (id.count(s)) {
		return id[s];
	}
	id[s] = ct;
	val[ct] = s;
	return ct++;
}

string min(const string &a, const string &b) {
	if (a == "-") {
		return b;
	}
	return a < b ? a : b;
}

bool lower_case(int id) {
	string str = val[id];
	for (int i = 0; i < str.length(); i++) {
		if (str[i] < 'a' || str[i] > 'z') {
			return false;
		}
	}
	return true;
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	int n, l;
	while (cin >> n >> l && n) {
		ct = 0;
		id.clear();
		ID("");
		for (int i = 0; i < S; i++) {
			trans[i].clear();
		}
		for (int i = 1; i <= n; i++) {
			string rule;
			cin >> rule;
			int left = ID(rule.substr(0, 1));
			int right = ID(rule.substr(2));
			trans[right].push_back(make_pair(left, 0));
			for (int j = 2; j < rule.length()-1; j++) {
				string str = rule.substr(j);
				int id = ID(str);
				int lft = ID(str.substr(0, 1));
				int rgt = ID(str.substr(1));
				trans[lft].push_back(make_pair(id, rgt));
				trans[rgt].push_back(make_pair(id, lft));
				car[id] = lft;
				cdr[id] = rgt;
			}
		}
		for (int i = 0; i < ct; i++) {
			for (int j = 0; j <= l; j++) {
				f[i][j] = "-";
			}
		}
		f[0][0] = "";
		for (int i = 0; i <= l; i++) {
			queue<int> q;
			for (int j = 0; j < ct; j++) {
				if (val[j].length() == i && lower_case(j)) {
					f[j][i] = val[j];
				}
				if (val[j].length() >= 2) {
					int lft = car[j], rgt = cdr[j];
					for (int k = 1; k < i; k++) {
						if (f[lft][k] != "-" && f[rgt][i-k] != "-") {
							f[j][i] = min(f[j][i], f[lft][k]+f[rgt][i-k]);
						}
					}
				}
				if (f[j][i] != "-") {
					q.push(j);
				}
			}
			while (!q.empty()) {
				int id = q.front();
				q.pop();
				vis[id] = false;
				for (int j = 0; j < trans[id].size(); j++) {
					int tar = trans[id][j].first, emp = trans[id][j].second;
					if (f[emp][0] == "" && (f[tar][i] == "-" || f[tar][i] > f[id][i])) {
						f[tar][i] = f[id][i];
						if (!vis[tar]) {
							q.push(tar);
							vis[tar] = true;
						}
					}
				}
			}
		}
		cout << f[ID("S")][l] << endl;
	}
	return 0;
}