#include <bits/stdc++.h>

using namespace std;

const int D = 1e3+5;
const int N = 11;
const int S = 1 << N;
int p[N], cnt[10];
long long f[S][D];
char s[N];
int n, d, t;

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%s", s);
		scanf("%d", &d);
		n = strlen(s);
		memset(cnt, 0, sizeof(cnt));
		memset(f, 0, sizeof(f));
		for (int i = 0; i < n; i++) {
			p[i] = s[i] - '0';
			cnt[p[i]]++;
		}
		f[0][0] = 1;
		for (int i = 0; i < (1 << n); i++) {
			for (int j = 0; j < d; j++) {
				for (int k = 0; k < n; k++) {
					if ((i & (1 << k)) == 0) {
						f[i | (1 << k)][(10 * j + p[k]) % d] += f[i][j];
					}
				}
			}
		}
		long long ans = f[(1 << n) - 1][0];
		for (int i = 0; i <= 9; i++) {
			for (int j = 1; j <= cnt[i]; j++) {
				ans /= j;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}