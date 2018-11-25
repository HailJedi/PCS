#include <bits/stdc++.h>

using namespace std;

const int N = 4e4+5;
const int INF = 1e9;

const int cost[5][5] = {
	1, 2, 2, 2, 2,
	INF, 1, 3, 4, 3,
	INF, 3, 1, 3, 4,
	INF, 4, 3, 1, 3,
	INF, 3, 4, 3, 1,
};

int f[N][5][5];
int a[N];
int n;

int dp(int d, int lf, int rf) {
	if (f[d][lf][rf] != -1) {
		return f[d][lf][rf];
	}
	if (d == n) {
		return f[d][lf][rf] = 0;
	}
	f[d][lf][rf] = INF;
	if (a[d+1] != lf) {
		f[d][lf][rf] = min(f[d][lf][rf], dp(d+1, lf, a[d+1]) + cost[rf][a[d+1]]);
	}
	if (a[d+1] != rf) {
		f[d][lf][rf] = min(f[d][lf][rf], dp(d+1, a[d+1], rf) + cost[lf][a[d+1]]);
	}
	return f[d][lf][rf];
}

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	while (true) {
		n = 1;
		while (cin >> a[n] && a[n]) {
			n++;
		}
		n--;
		if (n == 0) {
			break;
		}
		memset(f, -1, sizeof f);
		cout << dp(0, 0, 0) << endl;
	}
	return 0;
}
	
