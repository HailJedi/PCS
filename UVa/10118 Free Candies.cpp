#include <iostream>
#include <cstring>
#include <cstdio>
#define FOR(i, x, y) for (int i = x; i <= y; i++)
using namespace  std;

const int INF = 1e9;
const int maxn = 40+5;
const int maxc = 20;
int pile[4][maxn];
int dp[maxn][maxn][maxn][maxn];
int n;

void init() {
    memset(dp, -1, sizeof(dp));
    FOR(i, 0, maxn-1) FOR(j, 0, maxn-1)
    FOR(k, 0, maxn-1) FOR(l, 0, maxn-1)
    dp[i][j][k][l] = -1;
}

int solve(int *top, int s, int in) {
    if (in == 5) return 0;
    int &res = dp[top[0]][top[1]][top[2]][top[3]];
    if (res != -1) return res;
    res = 0;
    FOR(i, 0, 3)
    if (top[i] < n) {
        int take = pile[i][top[i]+1];
        top[i]++;
        if (s & (1<<take))
            res = max(res, solve(top, s^(1<<take), in-1) + 1);
        else
            res = max(res, solve(top, s|(1<<take), in+1));
        top[i]--;
    }
    return res;
}

int main()
{
    //freopen("read.in", "r", stdin);
    //freopen("write.out", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin >> n && n) {
        FOR (i, 1, n)
        cin >> pile[0][i] >> pile[1][i] >> pile[2][i] >> pile[3][i];
        init();
        int top[] = {0, 0, 0, 0};
        solve(top, 0, 0);
        cout << dp[0][0][0][0] << endl;
    }
    return 0;
}
