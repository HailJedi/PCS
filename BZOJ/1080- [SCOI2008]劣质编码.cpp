#include <bits/stdc++.h>

using namespace std;

const int N = 55;
string str[N];
int n;
vector<int> u, v, w;
map< vector<int>, int > Hash;
queue< vector<int> > q;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> str[i];
		if (str[i] == "") {
			cout << 0 << endl;
			return 0;
		} else {
			u.push_back(i << 6);
		}
	}
	Hash[u] = 0;
	q.push(u);
	while (!q.empty()) {
		u = q.front();
		q.pop();
		int h = Hash[u];
		for (int c = '0'; c <= '1'; c++) {
			int cnt = 0;
			v.clear();
			for (int i = 0; i < u.size(); i++) {
				int obj = u[i] >> 6, idx = u[i] & 63;
				if (str[obj][idx] == c) {
					if (++idx == str[obj].size()) {
						++cnt;
						for (int j = 1; j <= n; j++) {
							v.push_back(j << 6);
						}
					} else {
						v.push_back(obj << 6 | idx);
					}
				}
			}
			if (cnt >= 3) {
				cout << h + 1 << endl;
				return 0;
			}
			sort(v.begin(), v.end());
			if (!v.empty() && !Hash[v]) {
				Hash[v] = h + 1;
				q.push(v);
			}
		}
	}
	cout << -1 << endl;
	return 0;
}