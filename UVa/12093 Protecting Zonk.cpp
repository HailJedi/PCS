#include <cstdio>
#include <algorithm>
#define MIN(a, b, c) min(a, min(b, c))
using namespace std;

const int INF = 1e9;
const int maxn = 10000+5;
int N, C1, C2;
int dp[maxn][4];
int G[maxn][maxn];
int idx[maxn];

void dfs(int u, int fa) {
    dp[u][0] = dp[u][1] = 0;
    for (int i = 0; i < idx[u]; i++) {
        int v = G[u][i];
        if (v != fa) {
            dfs(v, u);
            dp[u][0] += MIN(dp[v][1], dp[v][2], dp[v][3]);
            dp[u][1] += min(dp[v][2], dp[v][3]);
        }
    }

    dp[u][3] = C2; dp[u][2] = C1;
    if (idx[u]) {
        int sum = 0; 
        for (int i = 0; i < idx[u]; i++) {
            int v = G[u][i];
            if (v != fa) {
                dp[u][3] += min(dp[v][0], MIN(dp[v][1], dp[v][2], dp[v][3]));
                sum += MIN(dp[v][1], dp[v][2], dp[v][3]);
            }
        }
        dp[u][2] += sum;   
        for (int i = 0; i < idx[u]; i++) {
            int v = G[u][i];
            if (v != fa) {
                dp[u][2] = min(dp[u][2], 
                    sum - MIN(dp[v][1], dp[v][2], dp[v][3]) + dp[v][3]);
            }
        }
    }
}

int main() {
    while (scanf("%d%d%d", &N, &C1, &C2) == 3 && N) {
        for (int i = 1; i <= N; i++) idx[i] = 0;
        for (int i = 1; i < N; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u][idx[u]++] = v;
            G[v][idx[v]++] = u;
        }
        dfs(1, 0);
        int ans = INF;
        for (int i = 1; i <= 3; i++)
            ans = min(ans, dp[1][i]);
        printf("%d\n", ans);
    }   
    return 0;
}