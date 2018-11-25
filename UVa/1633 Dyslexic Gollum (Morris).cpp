#include <cstdio>
#include <cstring>
// #include <vector>
#define maxn 400+5
#define maxk (10+2)
#define MOD (1e9+7)
using namespace std;

int N, K;
bool isPalin[maxk][1<<maxk];
int dp[maxn][1<<maxk];
int digit[maxk];
void recursion(int idx, int k) {
    if (idx == k) {
        int ok = 1, num = 0;
        for (int i = 0, j = k-1; i <= k-1; i++, j--) {
            if (digit[i] != digit[j]) return;
            num = num * 2 + digit[i];
        } 
        isPalin[k][num] = 1;
        return;
    }
    digit[idx] = 0;
    recursion(idx+1, k);
    digit[idx] = 1;
    recursion(idx+1, k);
}

void prepare() {
    for (int k = 1; k < maxk; k++) 
        recursion(0, k);
}

void solve() {
    if (N < K) {
        printf("%d\n", 1<<N);
        return;
    }

    for (int i = 0; i <= N; i++)
        for (int j = 0; j < (1<<K); j++)
            dp[i][j] = 0;
    
    for (int i = 0; i < (1<<K); i++)
        if (!isPalin[K][i]) dp[K][i]++;

    int base = (1<<K)-1;

    for (int k = K; k < N; k++) 
        for (int s = 0; s < (1<<K); s++) {
            if (isPalin[K][s] || !dp[k][s]) continue;
            int val = dp[k][s], x, y;
            x = ((s<<1)&base) | 0, y = (s<<1) | 0;
            if (!isPalin[K][x] && !isPalin[K+1][y])
                dp[k+1][x] = (dp[k+1][x] + val) % (int)MOD;
            x = ((s<<1)&base) | 1, y = (s<<1) | 1;
            if (!isPalin[K][x] && !isPalin[K+1][y])
                dp[k+1][x] = (dp[k+1][x] + val) % (int)MOD;
        }
    int ans = 0;
    for (int i = 0; i < (1<<K); i++) 
        ans = (ans + dp[N][i]) % (int)MOD;
    printf("%d\n", ans);
}

int main() {
    prepare();
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &N, &K);
        solve();
    }
    return 0;
}
