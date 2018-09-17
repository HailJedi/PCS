#include <bits/stdc++.h>

using namespace std;

const int N = 500010;
const int K = 110;
const int INF = 0x3f3f3f3f;
int n, k, p, sum[N], vec[N], dp[K][K];

int main() {
	scanf("%d %d %d", &n, &k, &p);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &sum[i]);
		sum[i] += sum[i-1];
		sum[i] %= p;
	}
	if (k*p > n) {
		for (int i = 0; i <= p; i++)
			for (int j = 0; j <= k; j++) dp[i][j] = INF;
		dp[0][0] = 0;
		for (int i = 1; i <= n; i++)
			for (int j = k; j >= 1; j--) 
				for (int m = 0; m < p; m++) 
					dp[sum[i]][j] = min(dp[sum[i]][j], dp[m][j-1]+(sum[i]-m+p)%p);
		cout << dp[sum[n]][k] << endl;
	} else {
		for (int i = 0; i <= n; i++) vec[i] = INF;
		for(int i = 1; i <= n-1; i++)
        	*upper_bound(vec+1, vec+n, sum[i]) = sum[i];
    	if(vec[k-1] <= sum[n]) cout << sum[n] << endl;
    	else cout << sum[n] + p << endl;
	}
	return 0;
}