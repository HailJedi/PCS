#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 1e6+5;
ll a[N], c[N];
int n;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	ll ave = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	 	ave += a[i];
	}
	ave /= n;
	for(int i = 2; i <= n; i++)
	   c[i] = c[i-1] + a[i] - ave;
	sort(c+1, c+n+1);
	ll ans = 0;
	int mid = c[(n >> 1) + 1];
	for(int i = 1; i <= n; i++)
	   ans += abs(c[i] - mid);
	cout << ans << endl;
	return 0;
}