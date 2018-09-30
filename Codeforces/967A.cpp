#include <bits/stdc++.h>

#define eb emplace_back
#define sz(x) x.size()
#define INF 1e9

using namespace std;

int n, r, h, m;
vector<int> t;

int main() {
	cin >> n >> r;
	t.eb(-r-1);
	for (int i = 1; i <= n; i++) {
		cin >> h >> m;
		t.eb(h*60+m);
	}
	t.eb(INF);
	for (int i = 0; i < sz(t)-1; i++) {
		int t1 = t[i], t2 = t[i+1];
		if (t2 - t1 >= 2 * (r+1)) {
			int st = t1 + 1 + r;
			cout << st / 60 << ' ' << st % 60 << endl;
			return 0;
		}
	}
	return 0;
}