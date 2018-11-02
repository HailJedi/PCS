#include <bits/stdc++.h>

using namespace std;

const int K = 101;
const int N = 16;
const int S = (1 << N);
int n, k, s;
int p[N], v[N], d[N];
double f[K][S];

int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= k; i++) {
		d[i] = 1 << (i - 1);
	}
	for (int i = 1; i <= k; i++) {
		scanf("%d", &v[i]);
		while (true) {
			scanf("%d", &s);
			if (s == 0) {
				break;
			}
			p[i] += d[s];
		}
	}
	for (int i = n; i >= 1; i--) {
		for (int j = 0; j < (1 << k); j++) {
			for (int l = 1; l <= k; l++) {
				if ((j & p[l]) == p[l]) {
					f[i][j] += max(f[i+1][j], f[i+1][j|(1<<(l-1))] + v[l]);
				} else {
					f[i][j] += f[i+1][j];
				}
			}
			f[i][j] /= k;
		}
	}
	printf("%.6lf\n", f[1][0]);
	return 0;
}