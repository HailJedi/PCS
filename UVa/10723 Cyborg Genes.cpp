#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 30+5;
int n, m;
char A[maxn], B[maxn];
int lcs[maxn][maxn], cnt[maxn][maxn];
int kase;

void LCS() {
	memset(lcs, 0, sizeof(lcs));
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < maxn; i++) {
		lcs[i][0] = lcs[0][i] = i;
		cnt[i][0] = cnt[0][i] = 1;
	}
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++) {
			if (A[i] == B[j]) {
				lcs[i][j] = lcs[i-1][j-1]+1;
				cnt[i][j] = cnt[i-1][j-1];
			} else {
				lcs[i][j] = min(lcs[i-1][j], lcs[i][j-1])+1;
				if (lcs[i-1][j] < lcs[i][j-1]) 
					cnt[i][j] = cnt[i-1][j];
				else if (lcs[i][j-1] < lcs[i-1][j]) 
					cnt[i][j] = cnt[i][j-1];
				else cnt[i][j] = cnt[i-1][j] + cnt[i][j-1];
			}
		}
}

void solve() {
	LCS();
	printf("Case #%d: %d %d\n", ++kase, lcs[n][m], cnt[n][m]);
}

int main() {
	int T; scanf("%d", &T);
	getchar();
	while (T--) {
		gets(A+1); gets(B+1);
		n = (int)strlen(A+1); 
		m = (int)strlen(B+1);
		solve();
	}
	return 0;
}