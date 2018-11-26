/*
Created 2018-11-26
"Birds"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
const int C = 10000 + 5;

long long f[2][C];
long long cost[N];
int c[N], sumc[N];
int n, W, B, X;

void update(long long &x, long long y) {
	if (x < y) {
		x = y;
	}
}

int main() {
	scanf("%d %d %d %d", &n, &W, &B, &X);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &c[i]);
		sumc[i] = sumc[i-1] + c[i];
	}
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &cost[i]);
	}
	int t = 0;
	memset(f[t], -1, sizeof f[t]);
	f[t][0] = W;
	for (int i = 1; i <= n; i++) {
		t ^= 1;
		memset(f[t], -1, sizeof f[t]);
		for (int j = 0; j <= sumc[i]; j++) {
			long long cap = W + 1LL * B * j;
			for (int k = min(c[i], j); k >= 0 && j-k <= sumc[i-1]; k--) {
				if (f[t^1][j-k] != -1) {
					long long rest = f[t^1][j-k] - cost[i] * k;
					if (rest >= 0) {
						long long mana = rest + X;
						update(f[t][j], min(cap, mana));
					}
				}
			}
		}
	}
	for (int i = sumc[n]; i >= 0; i--) {
		if (f[t][i] != -1) {
			printf("%d\n", i);
			break;
		}
	}
	return 0;
}
