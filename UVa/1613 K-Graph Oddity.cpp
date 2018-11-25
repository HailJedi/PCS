#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

vector<int> G[10000];

void add_edge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}

int n, m;
int valid[10000][10000];
int color[10000];
int vis[10000];

void solve () {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) valid[i][j] = 1;
    memset(vis, 0, sizeof(vis));
    
    int k = 0, col = 0;
    queue<int> q; q.push(1); vis[1] = 1;
    
    while (!q.empty()) {
        int v = q.front(); q.pop();
        
        k = max(k, (int)G[v].size());
        
        for (int c = 1; c <= n; c++) {
            if (!valid[v][c]) continue;
            
            color[v] = c;
            col = max(col, c);
            
            for (int i = 0; i < G[v].size(); i++) {
                int u = G[v][i];
                valid[u][c] = 0;
                if (vis[u]) continue;
                q.push(u); vis[u] = 1;
            }
            
            break;
        }
    }
    
    k = (k < col ? col : k);
    k = (k % 2 == 1 ? k : k + 1);
    
    cout << k << endl;
    for (int v = 1; v <= n; v++)
        cout << color[v] << endl;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    
    ios::sync_with_stdio(false);
    
    int u, v;
    bool first = false;
    
    while (cin >> n >> m && n != EOF) {
        if (first) cout << endl;
        else first = true;
        
        for (int i = 1; i <= n; i++) G[i].clear();
        
        while (m--) { cin >> u >> v; add_edge(u, v); }
        
        solve();
    }
    
    return 0;
}

