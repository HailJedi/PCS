#include <bits/stdc++.h>
using namespace std;

const int N = 55;
const int M = 2010;
const int INF = 0x3f3f3f3f;

int n, m, c, v, q;
int P[N], L[N], C[N], deg[N];
int f[N][N<<1][M], g[N][M], h[N][M];
vector< pair<int, int> > r[N];
bool root[N];
char op;

void dp(int x) {
    if(!r[x].size())
    {
        L[x] = min(L[x],m / C[x]);
        for(int i = 0; i <= L[x]; i++)
            for(int j = i; j <= L[x]; j++)
                f[x][i][j*C[x]] = (j - i) * P[x];
        return;
    }
    L[x] = INF;
    for (int i = 0; i < r[x].size(); i++)
    {
        pair<int, int> pr = r[x][i];
        int v = pr.first, q = pr.second;
        dp(v);
        L[x] = min(L[x],L[v] / q);
        C[x] += q * C[v];
    }
    L[x] = min(L[x],m / C[x]);
    memset(g, -INF, sizeof(g));
    g[0][0] = 0;
    for(int l = L[x]; l >= 0; l--)
    {
        int tot = 0;
        for (int i = 0; i < r[x].size(); i++)
        {
            pair<int, int> pr = r[x][i];
            int v = pr.first, q = pr.second;
            tot++;
            for(int j = 0; j <= m; j++)
                for(int k = 0; k <= j; k++)
                    g[tot][j] = max(g[tot][j], g[tot-1][j-k] + f[v][l*q][k]);
        }
        for(int j = 0; j <= l; j++)
            for(int k = 0; k <= m; k++)
                f[x][j][k] = max(f[x][j][k], g[tot][k] + P[x]*(l-j));
    }
}

int main() {
    scanf("%d %d", &n, &m);
    memset(root, true, sizeof(root));
    for (int i = 1; i <= n; i++) {
        scanf("%d %c", &P[i], &op);
        if (op == 'B') {
            scanf("%d %d", &C[i], &L[i]);
        } else {
            scanf("%d", &c);
            while (c--) {
                scanf("%d %d", &v, &q);
                r[i].push_back({v, q});
                root[v] = false;
            }
        }
    }
    int tot = 0;
    memset(f, -INF, sizeof(f));
    for (int i = 1; i <= n; i++) {
        if (root[i]) {
            dp(i); tot++;
            for (int j = 0; j <= m; j++) 
                for (int k = 0; k <= j; k++)
                    for (int l = 0; l <= L[i]; l++)
                        h[tot][j] = max(h[tot][j], h[tot-1][k]+f[i][l][j-k]);
        }
    }
    int ans = 0;
    for (int i = 0; i <= m; i++) ans = max(ans, h[tot][i]);
    printf("%d\n", ans);
    return 0;
}