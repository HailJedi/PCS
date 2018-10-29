/*
Created 2018-10-29
""
*/

#include <bits/stdc++.h>

using namespace std;

const int K = 10 + 5;
const int N = 50000 + 5;
const long long P = 1LL * 19260817;

int n, k;
char par[N];
int sum[N][K];
map<unsigned long long, int> cnt;

unsigned long long Hash(int *sum) {
	unsigned long long ret = 0;
	for (int i = 1; i <= k; i++) {
		ret = ret * P + sum[i];
	}
	return ret;
}

int main() {
	freopen("cbs.in", "r", stdin);
//	freopen("cbs.out", "w", stdout);
	scanf("%d %d", &k, &n);
	for (int i = 1; i <= k; i++) {
		scanf("%s", par+1);
		for (int j = 1; j <= n; j++) {
			sum[j][i] = sum[j-1][i] + (par[j] == '(' ? 1 : -1);
			printf("%3d", sum[j][i]);
		}
		cout << endl;
	}
	long long ans = 0;
	cnt[0] = 1;
	for (int i = 1; i <= n; i++) {
		unsigned long long hsh = Hash(sum[i]);
		cout << hsh << endl;
		ans += cnt[hsh];
		cnt[hsh]++;
	}
	printf("%lld\n", ans);
	return 0;
}
