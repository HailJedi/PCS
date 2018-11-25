#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 128
#define maxm 11
using namespace std;

int m, n, kase;
char feature[maxn][maxm];
int cnt[1<<maxm][1<<maxm], vis[1<<maxm][1<<maxm], d[1<<maxm][1<<maxm];

int dp(int s, int a) {
    if (cnt[s][a] <= 1) return 0;
    if (cnt[s][a] == 2) return 1;
    
    int &ans = d[s][a];
    if (vis[s][a] == kase) return ans;
    vis[s][a] = kase;
    
    ans = m;
    for (int k = 0; k < m; k++) {
        if (!(s & (1<<k))) {
            int s2 = s | (1<<k), a2 = a | (1<<k);
            if (cnt[s2][a] >= 1 && cnt[s2][a2] >= 1) {
                int need = max(dp(s2, a), dp(s2, a2)) + 1;
                ans = min(ans, need);
            }
        }
    }
    return ans;
}

void init() {
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++) {
        int fea = 0;
        for (int f = 0; f < m; f++)
            if (feature[i][f] == '1') fea |= (1<<f);
        for (int f = 0; f < (1<<m); f++)
            cnt[f][f&fea]++;
    }
}

int main() {
    memset(vis, 0, sizeof(vis));
    while (scanf("%d%d", &m, &n) == 2 && n) {
        for (int i = 0; i < n; i++) scanf("%s", feature[i]);
        init();
        kase++;
        printf("%d\n", dp(0, 0));
    }
    
    return 0;
}
