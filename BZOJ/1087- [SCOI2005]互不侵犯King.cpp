#include <bits/stdc++.h>

using namespace std;

const int N = 10;
const int S = (1 << N);
long long f[N][N*N][S];
int n, k;

bool good(int x) {
	return (x & (x >> 1)) == 0;
}

bool good2(int x, int y) {
	return (x & y) == 0 && (x & (y >> 1)) == 0 && (x & (y << 1)) == 0;
}

int dig(int x) {
	return __builtin_popcount(x);
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> k;
	for (int i = 0; i < (1 << n); i++) {
		if (good(i) && dig(i) <= k) {
			f[1][dig(i)][i] = 1;
		}
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < (1 << n); j++) {
			if (good(j)) {
				for (int l = 0; l < (1 << n); l++) {
					if (good(l) && good2(j, l)) {
						for (int p = dig(j); p + dig(l) <= k; p++) {
							f[i+1][p+dig(l)][l] += f[i][p][j];
						}
					}
				}
			}
		}
	}
	long long ans = 0;
	for (int i = 0; i < (1 << n); i++) {
		ans += f[n][k][i];
	}
	cout << ans << endl;
	return 0;
}