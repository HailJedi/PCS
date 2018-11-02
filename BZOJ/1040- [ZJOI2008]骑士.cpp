≠#include <bits/stdc++.h>

using namespace std;

const long long INF = 1e18;
const int N = 1e6+5;
vector<int> g[N];
int n, v, d, w;
int fa[N];
long long f[N][2], h[N][2][2];
int dfn[N], low[N];

void solve(int top, int bot) {
    for (int i = 0; i < 2; i++) {
        for (int u = bot; ; u = fa[u]) {
            h[u][0][i] = f[u][0];
            h[u][1][i] = f[u][1];
            if (u == top) break;
        }
        if (i) {
            h[fa[bot]][1][i] = -INF;
            h[fa[bot]][0][i] += max(h[bot][0][i], h[bot][1][i]);
        } else {
            h[fa[bot]][1][i] += h[bot][0][i];
            h[fa[bot]][0][i] += h[bot][0][i];
        }
        for (int u = fa[bot]; u != top; u = fa[u]) {
            h[fa[u]][0][i] += max(h[u][0][i], h[u][1][i]);
            h[fa[u]][1][i] += h[u][0][i];
        }
    }
    f[top][0] = max(f[top][0], max(h[top][0][0], h[top][0][1]));
    f[top][1] = max(f[top][1], h[top][1][0]);
}

void dfs(int u) {
    dfn[u] = low[u] = ++d;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v != fa[u]) {
            if (!dfn[v]) {
                fa[v] = u;
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else {
                if (dfn[v] < dfn[u]) {
                    low[u] = min(low[u], dfn[v]);
                }
                if (dfn[u] == low[v]) {
                    solve(u, v);
                }
            }
            if (dfn[u] < low[v]) {
                f[u][1] += f[v][0];
                f[u][0] += max(f[v][1], f[v][0]);
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int u = 1; u <= n; u++) {
        scanf("%d %d", &w, &v);
        f[u][1] = w;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int u = 1; u <= n; u++) {
        sort(g[u].begin(), g[u].end());
        g[u].resize(unique(g[u].begin(), g[u].end()) - g[u].begin());
    }
    long long ans = 0;
    for (int u = 1; u <= n; u++) {
        if (!dfn[u]) {
            dfs(u);
            ans += max(f[u][0], f[u][1]);
        }
    }
    printf("%lld\n", ans);
    return 0;
}