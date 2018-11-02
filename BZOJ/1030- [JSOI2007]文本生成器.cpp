#include <bits/stdc++.h>

using namespace std;

const int N = 100+5;
const int ST = 10000+5;
const int P = 10007;
int m, n;
char str[N];
int son[ST][26], fail[ST], dp[ST][N];
bool danger[ST];
int st = 1;

void insert(char *str) {
	int cur = 1, len = strlen(str);
	for (int i = 0; i < len; i++) {
		int c = str[i] - 'A';
		if (son[cur][c] == 0) {
			son[cur][c] = ++st;
		}
		cur = son[cur][c];
	}
	danger[cur] = true;
}

void match() {
	queue<int> q;
	q.push(1); 
	fail[1] = 0;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < 26; i++) {
			if (son[cur][i]) {
				int f = fail[cur];
				while (son[f][i] == 0) {
					f = fail[f];
				}
				fail[son[cur][i]] = son[f][i];
				danger[son[cur][i]] |= danger[son[f][i]];
				q.push(son[cur][i]);
			}
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < 26; i++) {
		son[0][i] = 1;
	}
	for (int i = 1; i <= n; i++) {
		scanf("%s", str);
		insert(str);
	}
	match();
	dp[1][0] = 1;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= st; j++) {
			if (!danger[j] && dp[j][i-1]) {
				for (int k = 0; k < 26; k++) {
					int cur = j;
					while (son[cur][k] == 0) {
						cur = fail[cur];
					}
					(dp[son[cur][k]][i] += dp[j][i-1]) %= P;
				}
			}
		}
	}
	int ans1 = 0, ans2 = 1;
	for (int i = 1; i <= m; i++) {
		(ans2 *= 26) %= P;
	}
	for (int i = 1; i <= st; i++) {
		if (!danger[i]) {
			(ans1 += dp[i][m]) %= P;
		}
	}
	printf("%d\n", (ans2 - ans1 + P) % P);
	return 0;
}