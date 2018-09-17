#include <bits/stdc++.h>
using namespace std;

const int N = 110;
const int V = 1010;
vector<pair<int, int>> ans;
int n, m, d[V];

void solve(int l, int r) {
	if (l > r) return ;
	if (l == r) {
		int b = d[l]+1;
		for (int i = 1; i <= b; i++)
			for (int j = i+1; j <= b; j++)
				ans.push_back(make_pair(i, j));
	} else {
		int p = d[l], q = d[r];
		int b = q + 1;
		for (int i = 0; i < p; i++)
			for (int j = 1; j < b-i; j++)
				ans.push_back(make_pair(b-i, j));
		for (int i = l+1; i <= r-1; i++)
			d[i] -= p;
		solve(l+1, r-1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> d[i];
	solve(1, n);
	cout << ans.size() << endl;
	for (auto e: ans)
		cout << e.first << ' ' << e.second << endl;
	return 0;
}