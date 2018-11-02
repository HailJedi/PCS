// 本地AC提交TLE

#include <bits/stdc++.h>

using namespace std;

const int N = 1e4+5;
const int LG = 22;
long long w[N*2];
int uv[N*2];
int n, m, q, u, v, d, idx;
vector<int> g[N];
int sum[N], fa[N][LG], tp[N], bt[N], dfn[N], low[N], depth2[N];
map<int, int> sz, id;

void dfs(int u, int f) {
    dfn[u] = low[u] = ++d;
    depth2[u] = depth2[f] + 1;
    for (int i = 0; i < g[u].size(); i++) {
        int e = g[u][i];
        int v = uv[e] - u;
        if (v != f) {
            if (!dfn[v]) {
                fa[v][0] = u;
                sum[v] = sum[u] + w[e];
                // assert(sum[v] == 0);
                dfs(v, u);
                low[u] = min(low[u], low[v]);
            } else
            if (dfn[v] < dfn[u]) {
                low[u] = min(low[u], dfn[v]);
            } else
            if (dfn[u] == low[v]) {
                for (int x = v; ; x = fa[x][0]) {
                    tp[x] = u;
                    bt[x] = v;
                    sz[x * 100000 + u] = sum[v] - sum[u] + w[e];
                    if (x == u) {
                        break;
                    }
                }
            }
        }
    }
}

typedef pair<int, int> pii;
#define mp make_pair
long long dist[N];
int depth[N];
#define INF 1e18
int bfa[N][LG];

void bfs() {
    priority_queue<pii> q;
    q.push(mp(0, 1));
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[1] = 0;
    while (!q.empty()) {
        pii pair = q.top(); q.pop();
        int u = pair.second, d = -pair.first;
        for (int i = 0; i < g[u].size(); i++) {
            int e = g[u][i], v = uv[e] - u;
            if (dist[v] > dist[u] + w[e]) {
                dist[v] = dist[u] + w[e];
                depth[v] = depth[u] + 1;
                q.push(mp(-dist[v], v));
                bfa[v][0] = u;
            }
        }
    }
    for (int i = 1; i < LG; i++) {
        for (int u = 1; u <= n; u++) {
            bfa[u][i] = bfa[bfa[u][i-1]][i-1];
            fa[u][i] = fa[fa[u][i-1]][i-1];
        }
    }
}

int LCA(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }
    for (int i = LG-1; i >= 0; i--) {
        if (depth[bfa[u][i]] >= depth[v]) {
            u = bfa[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = LG-1; i >= 0; i--) {
        if (bfa[u][i] != bfa[v][i]) {
            u = bfa[u][i], v = bfa[v][i];
        }
    }
    return bfa[u][0];
}

int LCA2(int u, int v) {
    if (depth2[u] < depth2[v]) {
        swap(u, v);
    }
    for (int i = LG-1; i >= 0; i--) {
        if (depth2[fa[u][i]] >= depth2[v]) {
            u = fa[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = LG-1; i >= 0; i--) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i], v = fa[v][i];
        }
    }
    return fa[u][0];
}

bool insamecycle(int u, int v) {
    int lca = LCA2(u, v);
    if (tp[u] && tp[v] && (lca == u || lca == v) && (tp[u] == tp[v] || tp[u] == v || tp[v] == u)) {
        return true;
    } else {
        return false;
    }
}

int aproach(int u, int lca) {
    if (insamecycle(u, lca)) {
        return u;
    }
    // cout << "aproaching " << lca << " from " << u << endl;
    for (int i = LG-1; i >= 0; i--) {
        if (bfa[u][i] && depth[bfa[u][i]] >= depth[lca] && !insamecycle(bfa[u][i], lca)) {
            u = bfa[u][i];
        }
    }
    u = bfa[u][0];
    // cout << " we got " << u << endl;
    // assert(insamecycle(u, lca));
    return u;
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    while (m--) {
        scanf("%d %d %lld", &u, &v, &w[m]);
        uv[m] = u + v;
        g[u].push_back(m);
        g[v].push_back(m);
    }
    dfs(1, 0);
    bfs();
    while (q--) {
        scanf("%d %d", &u, &v);
        // cout << u << ' ' << v << ": ";
        int lca = LCA(u, v);
        // cout << lca << ' ';
        if (bt[lca] == 0 || u == lca || v == lca) {
            printf("%lld\n", dist[u] + dist[v] - dist[lca] * 2);
        } else 
        if (insamecycle(u, v)) {
            long long path = abs(sum[u] - sum[v]);
            printf("%lld\n", min(path, sz[u * 100000 + tp[u]] - path));
        } else {
            int uu = aproach(u, lca), vv = aproach(v, lca);
            // cout << uu << ' ' << vv << ' ';
            if (bt[uu] != bt[vv]) {
                printf("%lld\n", dist[u] + dist[v] - dist[lca] * 2);
            } else {
                long long path = abs(sum[uu] - sum[vv]);
                // cout << path << ' ';
                printf("%lld\n", dist[u] - dist[uu] + dist[v] - dist[vv] + min(path, sz[uu * 100000 + tp[uu]] - path));
            }
        }
    }
    return 0;
}