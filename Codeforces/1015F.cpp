/*
Created 2018-11-28
"Bracket Substring"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 200 + 5;
const int mod = 1000000007;

int f[2][N][N];

void update(int &x, int y) {
	(x += y) %= mod;
}

char s[N];
int nxt[N], fail[N];

int main() {
	int n;
	scanf("%d %s", &n, s+1);
	n *= 2;
	int m = strlen(s+1), k = 0;
	for (int i = 2; i <= m; i++) {
		while (k && s[k+1] != s[i]) {
			k = nxt[k];	
		}
		if (s[k+1] == s[i]) {
			k++;
		}
		nxt[i] = k;
	}
	for (int i = 2; i <= m; i++) {	
		int k = nxt[i-1];
		while (k && s[k+1] == s[i]) {
			k = nxt[k];
		}
		if (s[k+1] != s[i]) {
			k++;
		}
		fail[i] = k;
	}
	fail[m+1] = m;
	int t = 0;
	f[t][0][0] = 1;
	for (int i = 0; i < n; i++) {
		memset(f[t^1], 0, sizeof f[t^1]);
		for (int j = 0; j <= n; j++) {
			for (int k = 0; k <= m; k++) {
				update(f[t^1][j+1][s[k+1] == '(' ? k + 1 : fail[k+1]], f[t][j][k]);
				if (j) {
					update(f[t^1][j-1][s[k+1] == ')' ? k+1 : fail[k+1]], f[t][j][k]);
				}
			}
		}
		t ^= 1;
	}
	printf("%d\n", f[t][0][m]);
	return 0;
}
