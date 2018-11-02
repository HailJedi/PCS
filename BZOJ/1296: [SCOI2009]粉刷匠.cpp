/*
Created 2018-11-02
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 5;
const int T = 2500 + 5;
const int INF = 0x3f3f3f3f;

long long row[N];
long long st[N];
int dp[N][T], dp2[N][T];
int f[T];
char str[N];

int main() {
	int n, m, t;
	scanf("%d %d %d", &n, &m, &t);
	t = min(t, m * n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", str);
		for (int j = 0; j < m; j++) {
			st[i] |= ((1LL * (str[j] == '1')) << j);
		}
	}
	for (int i = 1; i <= m; i++) {
		row[i] = (1LL << i) - 1;
	}
	for (int r = 1; r <= n; r++) {
		memset(dp, 0, sizeof dp);
		for (int k = 1; k <= min(t, m); k++) {
			for (int i = k; i <= m; i++) {
				for (int j = k-1; j < i; j++) {
					long long s = ((st[r] >> j) & row[i-j]);
					int cnt = __builtin_popcountll(s);
					dp[i][k] = max(dp[i][k], dp[j][k-1] + max(cnt, i-j-cnt));
				}
			}
			dp2[r][k] = dp[m][k];
		}
	}
	for (int k = 0; k <= t; k++) {
		f[k] = dp2[1][k];
	}
	for (int r = 2; r <= n; r++) {
		for (int k = min(t, r*m); k >= 0; k--) {
			for (int tk = 0; tk <= min(m, k); tk++) {
				f[k] = max(f[k], f[k-tk] + dp2[r][tk]);
			}
		}
	}
	printf("%d\n", *max_element(f, f+1+t));
	return 0;
}
	
