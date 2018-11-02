#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 1e3+5;
vector<int> primes;
ll dp[N][N];
bool isprime[N];
int n;

int main() {
	cin >> n;
	memset(isprime, true, sizeof(isprime));
	primes.push_back(1);
	for (int i = 2; i <= n; i++) {
		if (isprime[i]) {
			primes.push_back(i);
			for (int j = 2 * i; j <= n; j += i) {
				isprime[j] = false;
			}
		}
	}
	int m = primes.size() - 1;
	dp[0][0] = 1;
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			dp[i][j] = dp[i-1][j];
		}
		for (int j = primes[i]; j <= n; j *= primes[i]) {
			for (int k = j; k <= n; k++) {
				dp[i][k] += dp[i-1][k-j];
			}
		}
	}
	ll ans = 0;
	for (int i = 0; i <= n; i++) {
		ans += dp[m][i];
	}
	cout << ans << endl;
	return 0;
}