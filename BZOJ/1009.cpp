/*
Created 2018-12-03
"[HNOI2008]GT考试"
*/

#include <bits/stdc++.h>

using namespace std;

const int M = 100 + 5;

int n, m, mod;
char str[M];

int tr[2][M][M];
int I[2][M][M];
int suf[M];

int main() {
	scanf("%d %d %d %s", &n, &m, &mod, str+1);
	int k = 0;
	for (int i = 2; i < m; i++) {
		while (k && str[i] != str[k+1]) {
			k = suf[k];
		}
		k += str[i] == str[k+1];
		suf[i] = k;
	}
	int ti = 0, tt = 0;
	for (int i = 0; i < m; i++) {
		for (char c = '0'; c <= '9'; c++) {
			if (c == str[i+1]) {
				tr[tt][i][i+1]++;
			} else {
				int k = suf[i];
				while (k && str[k+1] != c) {
					k = suf[k];
				}
				k += str[k+1] == c;
				tr[tt][i][k]++;                        
			}
		}
	}
	for (int i = 0; i < m; i++) {
		I[ti][i][i] = 1;
	}
	while (n) {
		if (n & 1) {
			ti ^= 1;
			memset(I[ti], 0, sizeof I[ti]);
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < m; j++) {
					for (int k = 0; k < m; k++) {
						(I[ti][i][j] += I[ti^1][i][k] * tr[tt][k][j]) %= mod;
					}
				}
			}
		}
		tt ^= 1;
		memset(tr[tt], 0, sizeof tr[tt]);
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				for (int k = 0; k < m; k++) {
					(tr[tt][i][j] += tr[tt^1][i][k] * tr[tt^1][k][j]) %= mod;
				}
			}
		}
		n >>= 1;
	}
	int sum = 0;
	for (int i = 0; i < m; i++) {
		(sum += I[ti][0][i]) %= mod;
	}
	printf("%d\n", sum);
	return 0;
}
