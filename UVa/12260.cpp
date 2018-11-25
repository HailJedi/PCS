#include <bits/stdc++.h>

using namespace std;

const int N = 1e3+5;

pair<int, int> f[N][N];
pair<int, int> val[N];

bool cmp(pair<int, int> p1, pair<int, int> p2) {
	if (p1.first != p2.first) {
		return p1.first > p2.first;
	}
	return p1.second < p2.second;
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	int T;
	cin >> T;
	while (T--) {
		int n;
		string first;
		cin >> n >> first;
		for (int i = 1; i <= n; i++) {
			cin >> val[i].first >> val[i].second;
		}
		sort(val+1, val+1+n, cmp);
		int base = 0;
		if (first == "Petra") {
			base = val[1].first;
			for (int i = 1; i < n; i++) {
				val[i] = val[i+1];
			}
			n--;
		}
		memset(f, 0, sizeof f);
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= (i+1)/2; j++) {
				f[i][j] = make_pair(f[i-1][j].first, f[i-1][j].second + val[i].first);
				if (j != 0) {
					f[i][j] = max(f[i][j], make_pair(f[i-1][j-1].first + val[i].second, f[i-1][j-1].second));
				}
			}
		}
		cout << f[n][(n+1)/2].second + base << ' ' << f[n][(n+1)/2].first << endl;
	}
	return 0;
}