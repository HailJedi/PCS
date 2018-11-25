#include <bits/stdc++.h>

using namespace std;

const int N = 1e4+5;
const int INF = 0x3f3f3f3f;

int a[N];
int lis[N];
int lf[N], rf[N];

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	int n;
	while (cin >> n) {
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		memset(lis, INF, sizeof lis);
		for (int i = 1; i <= n; i++) {
			int *it = lower_bound(lis, lis+N, a[i]);	
			lis[it - lis] = a[i];
			lf[i] = it - lis + 1;
		}
		memset(lis, INF, sizeof lis);
		for (int i = n; i >= 1; i--) {
			int *it = lower_bound(lis, lis+N, a[i]);
			lis[it - lis] = a[i];
			rf[i] = it - lis + 1;
		}
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			int t = min(lf[i], rf[i]);
			ans = max(ans, 2 * t - 1);
		}
		cout << ans << endl;
	}
	return 0;
}
		