/*
Created 2018-11-28
"Streets and Avenues in Berhattan"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 30000 + 5;
const int K = 200000 + 5;

char name[K];
int cnt[26];
bool f[N+K];

int main() {
	int T, n, m, k;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d %s", &n, &m, &k, name);
		memset(cnt, 0, sizeof cnt);
		int mx = 0;
		for (int i = 0; i < k; i++) {
			cnt[name[i]-'A']++;
		}
		mx = *max_element(cnt, cnt+26);
		int ans = 1e9;
		memset(f, false, sizeof f);
		f[0] = 1;
		for (int j = 0; j < 26; j++) if (cnt[j]) {
			for (int l = n+k; l >= cnt[j]; l--) {
				f[l] |= f[l-cnt[j]];
			}
		}
		if (f[n]) {
			puts("0");
			continue;
		}
		for (int i = 0; i < 26; i++) if (cnt[i]) {
			memset(f, false, sizeof f);
			f[0] = 1;
			for (int j = 0; j < 26; j++) if (cnt[j] && j != i) {
				for (int l = n+mx-1; l >= cnt[j]; l--) {
					f[l] |= f[l-cnt[j]];
				}
			}
			for (int j = 0; j <= n+mx-1; j++) if (f[j]) {
				int l = k - cnt[i] - j;
				int r = max(0, n-j), c = max(0, m-l);
				if (r + c <= cnt[i]) {
					ans = min(ans, r * c);
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
