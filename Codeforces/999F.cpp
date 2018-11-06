/*
Created 2018-11-06
"Cards and Joy"
*/

#include <bits/stdc++.h>

using namespace std;

const int V = 100000 + 5;
const int N = 500 + 5;
const int K = 10 + 5;

int n, k;
int card[V];
int player[V];
int h[K];
int f[N*K];

int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n * k; i++) {
		int c;
		scanf("%d", &c);
		card[c]++;
	}
	for (int i = 1; i <= n; i++) {
		int f;
		scanf("%d", &f);
		player[f]++;
	}
	for (int i = 1; i <= k; i++) {
		scanf("%d", &h[i]);
	}
	int ans = 0;
	for (int i = 1; i < V; i++) {
		if (card[i] && player[i]) {
			if (card[i] >= k * player[i]) {
				ans += player[i] * h[k];
			} else {
				memset(f, 0, sizeof f);
				for (int p = 1; p <= player[i]; p++) {
					for (int j = card[i]; j >= 1; j--) {
						for (int t = 1; t <= k; t++) {
							if (j - t >= 0) {
								f[j] = max(f[j], f[j-t] + h[t]);
							}
						}
					}
				}
				ans += f[card[i]];
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
