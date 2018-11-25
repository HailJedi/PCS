#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxt 200+5
#define maxn 50+5
#define INF 0x3f3f3f3f
using namespace std;

int dp[maxt][maxn];
int has_train[maxt][maxn][2];
int tim[maxn];
int N, T, M, x;

bool input() {
    scanf("%d", &N);
    if (N == 0) return false;
    scanf("%d", &T);
    for (int i = 1; i <= N-1; i++) scanf("%d", &tim[i]);
    memset(has_train, 0, sizeof(has_train));
    scanf("%d", &M);
    while (M--) {
        scanf("%d", &x);
        for (int i = 1; i <= N-1; i++) {
            if (x <= T) has_train[x][i][0] = 1;
            x += tim[i];
        }
    }
    scanf("%d", &M);
    while (M--) {
        scanf("%d", &x);
        for (int i = N-1; i >= 1; i--) {
            if (x <= T) has_train[x][i+1][1] = 1;
            x += tim[i];
        }
    }
    return true;
}

void solve() {
    for (int i = 1; i <= N-1; i++) dp[T][i] = INF;
    dp[T][N] = 0;
    
    for (int t = T-1; t >= 0; t--)
        for (int s = 1; s <= N; s++) {
            dp[t][s] = dp[t+1][s] + 1;
            if (has_train[t][s][0] && t + tim[s] <= T && s < N)
                dp[t][s] = min(dp[t][s], dp[t+tim[s]][s+1]);
            if (has_train[t][s][1] && t + tim[s-1] <= T && s > 1)
                dp[t][s] = min(dp[t][s], dp[t+tim[s-1]][s-1]);
        }
}

void output(int kase) {
    printf("Case Number %d: ", kase);
    if (dp[0][1] >= INF) puts("impossible");
    else printf("%d\n", dp[0][1]);
}

int main() {
    for (int kase = 1; ; kase++) {
        if (!input()) break;
        solve();
        output(kase);
    }
    return 0;
}
