#include <cstdio>
#include <cstring>
#include <algorithm>
#define INF 0x3f3f3f3f
using namespace std;

typedef long long ll;

int R, C;
int dp[15][105];
int A[15][105];
int nxt[15][105];

int main() {
    while (scanf("%d%d", &R, &C) == 2 && R != EOF) {
        for (int i = 1; i <= R; i++)
            for (int j = 1; j <= C; j++)
                scanf("%d", &A[i][j]);
        
        int ans = INF, first = 1;
        for (int c = C; c >= 1; c--) {
            for (int r = 1; r <= R; r++) {
                if (c == C) dp[r][c] = A[r][c];
                else { 
                    int row[3] = {r, r-1, r+1};
                    if (r == R) row[2] = 1;
                    if (r == 1) row[1] = R;
                    sort(row, row+3);
                    dp[r][c] = INF;
                    for (int k = 0; k < 3; k++) {
                        int cmp = dp[row[k]][c+1] + A[r][c];
                        if (cmp < dp[r][c]) {
                            dp[r][c] = cmp;
                            nxt[r][c] = row[k];
                        }
                    }
                }
                if (c == 1 && dp[r][c] < ans) { first = r; ans = dp[r][c]; }
            }
        }
        
        printf("%d", first);
        for (int r = nxt[first][1], c = 2; c <= C; r = nxt[r][c], c++)
            printf(" %d", r);
        printf("\n%d\n", ans);
    }
    return 0;
}
