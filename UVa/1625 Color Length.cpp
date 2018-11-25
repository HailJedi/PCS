#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 5010
#define INF 0x3f3f3f3f
using namespace std;

char p[maxn], q[maxn];
int sp[26], sq[26], ep[26], eq[26];
int dp[2][maxn], c[2][maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s%s", p+1, q+1);
        
        int n = (int)strlen(p+1);
        int m = (int)strlen(q+1);
        for (int i = 1; i <= n; i++) p[i] -= 'A';
        for (int i = 1; i <= m; i++) q[i] -= 'A';
        
        for (int i = 0; i < 26; i++) {
            sp[i] = sq[i] = INF;
            ep[i] = eq[i] = 0;
        }
        for (int i = 1; i <= n; i++) {
            sp[p[i]] = min(sp[p[i]], i);
            ep[p[i]] = i;
        }
        for (int i = 1; i <= m; i++) {
            sq[q[i]] = min(sq[q[i]], i);
            eq[q[i]] = i;
        }
        
        int t = 0;
        memset(dp, 0, sizeof(dp));
        memset(c, 0, sizeof(c));
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (!i && !j) continue;
                
                int v1 = INF, v2 = INF;
                if (i) v1 = dp[t^1][j] + c[t^1][j];
                if (j) v2 = dp[t][j-1] + c[t][j-1];
                dp[t][j] = min(v1, v2);
                
                if (i) {
                    c[t][j] = c[t^1][j];
                    if (sp[p[i]] == i && sq[p[i]] > j) c[t][j]++;
                    if (ep[p[i]] == i && eq[p[i]] <= j) c[t][j]--;
                } else if (j) {
                    c[t][j] = c[t][j-1];
                    if (sq[q[j]] == j) c[t][j]++;
                    if (eq[q[j]] == j && ep[q[j]] <= 0) c[t][j]--;
                }
            }
            t ^= 1;
        }
        printf("%d\n", dp[t^1][m]);
    }
    return 0;
}

