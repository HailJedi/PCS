#include <bits/stdc++.h>

using namespace std;

const int N = 1e3+5;
const int INF = 1e9;

long long f[N], g[N];
int d[N];
int sum[N];

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	int n, l, c, kase = 0, first = 1;
	while (cin >> n && n) {
		if (!first) {
			cout << endl;
		}
		first = 0;
		cin >> l >> c;
		for (int i = 1; i <= n; i++) {
			cin >> d[i];
			sum[i] = sum[i-1] + d[i];
		}
		f[0] = 0;
		for (int i = 1; i <= n; i++) {
			f[i] = INF;
			for (int j = 0; j < i; j++) {
				if (sum[i] - sum[j] <= l) {
					f[i] = min(f[i], f[j] + 1);
				}
			}
		}
		g[0] = 0;
		for (int i = 1; i <= n; i++) {
			g[i] = INF;
			for (int j = 0; j < i; j++) {
				if (sum[i] - sum[j] <= l && f[i] == f[j] + 1) {
					int t = l - sum[i] + sum[j];
					int cost = t == 0 ? 0 : t <= 10 ? -c : (t-10) * (t-10);
					g[i] = min(g[i], g[j] + cost);
				}
			}
		}
		cout << "Case " << ++kase << ":" << endl;
		cout << "Minimum number of lectures: " << f[n] << endl;
		cout << "Total dissatisfaction index: " << g[n] << endl;
	}
	return 0;
}