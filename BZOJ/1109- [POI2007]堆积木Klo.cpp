#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;
pair<int, int> dat[N];
#define fs first
#define sc second
int n, x, ct;
int lis[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> x;
		if (i - x >= 0) {
			dat[++ct].fs = i - x, dat[ct].sc = x;	
		}
	}
	sort(dat+1, dat+1+ct);
	fill(lis, lis+2+n, 2e9);
	int ans = 0;
	for (int i = 1; i <= ct; i++) {
		int it = lower_bound(lis+1, lis+1+n, dat[i].sc) - lis;
		lis[it] = dat[i].sc;
	}
	cout << lower_bound(lis+1, lis+1+n, 2e9) - lis - 1 << endl;
	return 0;
}