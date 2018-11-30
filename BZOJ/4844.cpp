/*
Created 2018-11-30
"[Neerc2016]Foreign Postcards"
*/

#include <bits/stdc++.h>
#pragma GCC optimize (2)
#pragma G++ optimize (2)

using namespace std;

const int N = 1000000 + 5;

char dir[N];
long long s[2], sums[2], sum[2];
double f[2], sumf[2];

int main() {
	scanf("%s", dir+1);
	int n = strlen(dir+1);
	reverse(dir+1, dir+1+n);
	int t = 0;
	for (int i = 1; i <= n; i++) {
		t ^= 1;
		s[t] = s[t^1] + (dir[i] == 'C');
		sum[t] = sum[t^1] + i;
		sums[t] = sums[t^1] + s[t];
		if (dir[i] == 'W') {
			f[t] = s[t] + (sumf[t^1] - sums[t^1]) / i;
		} else {
			f[t] = i - s[t] + (sumf[t^1] + sums[t^1] - sum[t^1]) / i;
		}
		sumf[t] = sumf[t^1] + f[t];
	}
	printf("%.10lf\n", f[t]);
	return 0;
}
