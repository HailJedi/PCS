#include <cstdio>
#include <vector>
#include <algorithm>
#define INF 1000000000
#define maxn 10010
using namespace std;

vector<int> G[maxn], vertices;
int n, u, v;
int d[maxn][3], pa[maxn];

void dfs(int u, int f) {
    vertices.push_back(u);
    pa[u] = f;
    for (int i = 0; i < (int)G[u].size(); i++) {
        int v = G[u][i];
        if (v == f) continue;
        dfs(v, u);
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) G[i].clear();
        vertices.clear();
        for (int i = 1; i < n; i++) {
            scanf("%d%d", &u, &v); u--; v--;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(0, -1);
        
        for (int i = (int)vertices.size()-1; i >= 0; i--) {
            int u = vertices[i];
            d[u][0] = 1; d[u][1] = 0;
            for (int j = 0; j < (int)G[u].size(); j++) {
                int v = G[u][j];
                if (v == pa[u]) continue;
                d[u][0] += min(d[v][0], d[v][1]);
                d[u][1] += d[v][2];
                if (d[u][0] > INF) d[u][0] = INF;
                if (d[u][1] > INF) d[u][1] = INF;
            }
            d[u][2] = INF;
            for (int j = 0; j < (int)G[u].size(); j++) {
                int v = G[u][j];
                if (v == pa[u]) continue;
                d[u][2] = min(d[u][2], d[u][1] - d[v][2] + d[v][0]);
            }
        }
        printf("%d\n", min(d[0][0], d[0][2]));
        scanf("%d", &n);
    }
    return 0;
}
