#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 500+5;
const int INF = 1e9;

int N;
int _size[maxn];
int cost[maxn][maxn][2];

int calc(int l, int r) {
	const int len = r - l + 1;
	int dp[len+1][len+1] = {0};
	for (int i = 1; i <= len; i++)
		for (int j = 1; j <= len; j++) dp[i][j] = INF;

	for (int i = 1; i <= len; i++) {
		dp[i][i] = 0;
		for (int j = 1; j <= len; j++) {
			for (int k = i; k <= len; k++) {
				if (dp[j][k] >= INF) continue;
				if (j-1 >= 1) 
					dp[j-1][k] = min(dp[j-1][k], dp[j][k] + cost[j-1][k][0]);
				if (k+1 <= len)
					dp[j][k+1] = min(dp[j][k+1], dp[j][k] + cost[j][k+1][1]);
			}
		}
	}

	return dp[1][len];
}

int solve(int l, int r) {
	if (l == r) return _size[l] == 1 ? 0 : INF;

	int ret = INF;
	int exist[maxn] = {0};

	int maxs = 0;
	for (int i = l; i <= r; i++) {
		exist[_size[i]]++; 
		maxs = max(maxs, _size[i]);
	}

	bool ok = true; 
	for (int i = 1; i <= maxs; i++) {
		if (!exist[i]) return INF;
		if (exist[i] >= 2) ok = false;
	}
	if (ok) return calc(l, r);
	else 
		for (int i = l; i < r; i++)
			ret = min(ret, solve(l, i) + solve(i+1, r));

	return ret;
}

vector<int>::iterator it;

int main() {
	while (scanf("%d", &N) == 1) {
		for (int i = 1; i <= N; i++)
			scanf("%d", &_size[i]);

		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				cost[i][j][0] = cost[i][j][1] = 0;

		vector<int> vec[N+1][N+1];
		for (int i = 1; i <= N; i++) {
			for (int j = i; j <= N; j++) {
				vector<int> &v = vec[i][j];
				for (int k = i; k <= j; k++) 
					v.push_back(_size[k]);
				sort(v.begin(), v.end());
				// calculate p = 0
				int left = _size[i];
				int &c0 = cost[i][j][0]; 
				it = lower_bound(v.begin(), v.end(), left);
				c0 += v.end() - it - 1;
				if (it != v.begin()) c0++;
				// calculate p = 1
				int right = _size[j];
				int &c1 = cost[i][j][1];
				it = lower_bound(v.begin(), v.end(), right);
				c1 += v.end() - it - 1;
				if (it != v.begin()) c1++;
			}
		}

		int ans = solve(1, N);
		if (ans != INF) printf("%d\n", ans);
		else puts("impossible");
	}
	return 0;
}