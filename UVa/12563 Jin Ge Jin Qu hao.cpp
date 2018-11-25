#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 55
#define INF 1000000000
using namespace std;

int n, t;
int dp[2][maxn*180+678], l[maxn];

int main() {
    int T; scanf("%d", &T);
    for (int kase = 1; kase <= T; kase++) {
        scanf("%d%d", &n, &t);
        for (int i = 1; i <= n; i++) scanf("%d", &l[i]);
        
        for (int i = 1; i <= t-1; i++) dp[0][i] = -1;
        dp[0][0] = 0;
        
        int p = 1, ans = -INF;
        for (int i = 1; i <= n; i++) {
            for (int j = t-1; j >= 0; j--) {
                dp[p][j] = dp[p^1][j];
                if (j >= l[i] && dp[p^1][j-l[i]] >= 0)
                    dp[p][j] = max(dp[p][j], dp[p^1][j-l[i]]+1);
                ans = max(ans, dp[p][j]);
            }
            p ^= 1;
        }
        
        for (int i = t-1; i >= 0; i--)
            if (dp[p^1][i] == ans) {
                printf("Case %d: %d %d\n", kase, ans+1, i + 678);
                break;
            }
    }
    return 0;
}
