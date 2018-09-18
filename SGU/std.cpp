#include <stdio.h>
#include <iostream>
#include <memory.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int,bool> PIB;
typedef long long LL;
#define maxn 510
#define mod 1000000009

int n ,k;
PIB xu[maxn << 1];
LL dp[2][maxn][maxn];

void read() {
	int x;
	for(int i = 0 ;i < n;i++) {
		scanf("%d",&x);
		xu[i] = make_pair(x, true);
	}
	for(int i = n;i < 2 * n;i++) {
		scanf("%d",&x);
		xu[i] = make_pair(x, false);
	}
	sort(xu , xu + 2 * n);
}

int solve() {
	int s1 = 0, s2 = 0;
	memset(dp, 0, sizeof(dp));
	dp[0][0][0] = 1;
	for(int i = 0 ;i < 2 * n;i++) {
		int now = i % 2;
		int to = 1 - now;
		for(int f = 0;f <= n; f++)
			for(int g = 0;g <= n;g++) {
				if(0 == dp[now][f][g])
					continue;
				int l1 = s1 - f - g;
				int l2 = s2 - f - g;
				dp[to][f][g] = (dp[now][f][g] + dp[to][f][g]) % mod;
				if(true == xu[i].second) {
					dp[to][f+1][g] = (dp[to][f+1][g] + dp[now][f][g] * l2) % mod;
				}
				else {
					dp[to][f][g+1] = (dp[to][f][g+1] + dp[now][f][g] * l1) % mod;
				}
			}
		if(true == xu[i].second)
			s1 ++;
		else
			s2 ++;
		memset(dp[now], 0, sizeof(dp[now])); 
	}

	int a = (n + k) / 2;
	int b = (n - k) / 2;
	return dp[0][a][b];
}

int main() {
	cin >> n >> k;
	read();
	if(1 == (n + k) % 2) {
		cout << "0" << endl;
		return 0;
	}
	cout << solve() << endl;
	return 0;
}
