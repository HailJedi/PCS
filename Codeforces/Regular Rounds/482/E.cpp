#include <iostream>
using namespace std;

const int N = 55, MOD = 1E9 + 7;

int n, p, c[N];
long long ans = 0, pw[N], f[N][N][N][N];

void init()
{
    f[0][0][0][0] = 1;
    pw[0] = 1;
    for (int i = 1; i < N; i++)
        pw[i] = pw[i - 1] * 2 % MOD;
}

void find_ans(int ob, int eb, int ow, int ew, int col, long long &ret)
{
    // current node is even-white
    if (col != 0 && ew != 0)
        (ret += f[ob][eb][ow][ew - 1] * pw[ow + ew - 1 + eb] % MOD * (ob ? pw[ob-1] : 0) % MOD) %= MOD;

    // current node is odd-white
    if (col != 0 && ow != 0)
        (ret += f[ob][eb][ow - 1][ew] * pw[ow - 1 + ew + eb] % MOD * (ob ? pw[ob-1] : 1) % MOD) %= MOD;

    // current node is even-black
    if (col != 1 && eb != 0)
        (ret += f[ob][eb - 1][ow][ew] * pw[ob + eb - 1 + ew] % MOD * (ow ? pw[ow-1] : 0) % MOD) %= MOD;

    // current node is odd-black
    if (col != 1 && ob != 0)
        (ret += f[ob - 1][eb][ow][ew] * pw[ob - 1 + eb + ew] % MOD * (ow ? pw[ow-1] : 1) % MOD) %= MOD;
}

int main()
{
    init();
    scanf("%d%d", &n, &p);
    for (int i = 1; i <= n; i++)
        scanf("%d", c + i);
    for (int i = 1; i <= n; i++)
        for (int ob = 0; ob <= i; ob++)
            for (int eb = 0; ob + eb <= i; eb++)
                for (int ow = 0; ob + eb + ow <= i; ow++)
                {
                    int ew = i - ob - eb - ow;
                    find_ans(ob, eb, ow, ew, c[i], f[ob][eb][ow][ew]);
                    if (i == n && ((ob + ow) & 1) == p)
                        (ans += f[ob][eb][ow][ew]) %= MOD;
                }
    printf("%lld\n", ans);
    return 0;
}