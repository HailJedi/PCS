#include <bits/stdc++.h>

using namespace std;

const int N = 300;
const int INF = 0x3f3f3f3f;

int prince[N*N], princess[N*N];
int mp[N*N], lis[N*N];
int t, n, p, q, kase;

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> t;
	while (t--) {
		
		memset(mp, 0, sizeof mp);

		cin >> n >> p >> q;
		for (int i = 1; i <= p + 1; i++) {
			cin >> prince[i];
			mp[prince[i]] = i;
		}
		for (int i = 1; i <= q + 1; i++) {
			cin >> princess[i];
			princess[i] = mp[princess[i]];
		}

		memset(lis, INF, sizeof lis);
		for (int i = 1; i <= q + 1; i++) {
			int *it = lower_bound(lis, lis + N * N, princess[i]);
			lis[it - lis] = princess[i];
		}
			
		int ans = lower_bound(lis, lis + N * N, INF) - lis;
		cout << "Case " << ++kase << ": " << ans << endl;

	}
	
	return 0;
}