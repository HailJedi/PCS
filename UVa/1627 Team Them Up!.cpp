
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define maxn 110
using namespace std;

int n, cc;
int color[maxn], diff[maxn];
int G[maxn][maxn], d[maxn][maxn*2];
vector<int> team[maxn][2];

bool paint(int u, int c) {
    color[u] = c;
    team[cc][c-1].push_back(u);
    for (int v = 0; v < n; v++) {
        if (u != v && !(G[u][v] && G[v][u])) {
            if (color[v] == color[u]) return false;
            if (!color[v] && !paint(v, 3-c)) return false;
        }
    }
    return true;
}

bool build() {
    memset(color, 0, sizeof(color));
    cc = 0;
    for (int i = 0; i < n; i++)
        if (!color[i]) {
            team[cc][0].clear();
            team[cc][1].clear();
            if (!paint(i, 1)) return false;
            diff[cc] = (int)(team[cc][0].size() - team[cc][1].size());
            cc++;
        }
    return true;
}

void print(int ans) {
    vector<int> team1, team2;
    for (int i = cc-1; i >= 0; i--) {
        int t = 0;
        if (d[i][ans-diff[i]+n]) { t = 0; ans -= diff[i]; }
        else { t = 1; ans += diff[i]; }
        for (int j = 0; j < team[i][t].size(); j++)
            team1.push_back(team[i][t][j]);
        for (int j = 0; j < team[i][t^1].size(); j++)
            team2.push_back(team[i][t^1][j]);
    }
    printf("%d", (int)team1.size());
    for (int i = 0; i < team1.size(); i++) printf(" %d", team1[i]+1);
    puts("");
    printf("%d", (int)team2.size());
    for (int i = 0; i < team2.size(); i++) printf(" %d", team2[i]+1);
    puts("");
}

void dp() {
    memset(d, 0, sizeof(d));
    d[0][0+n] = 1;
    for (int i = 0; i < cc; i++)
        for (int j = -n; j <= n; j++) {
            if (!d[i][j+n]) continue;
            d[i+1][j+diff[i]+n] = 1;
            d[i+1][j-diff[i]+n] = 1;
        }
    for (int ans = 0; ans <= n; ans++) {
        if (d[cc][ans+n]) { print(ans); break; }
        if (d[cc][-ans+n]) { print(-ans); break; }
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        memset(G, 0, sizeof(G));
        for (int u = 0; u < n; u++) {
            int v;
            while (scanf("%d", &v) == 1 && v) G[u][v-1] = 1;
        }
        
        if (n == 1 || !build()) puts("No solution");
        else dp();
        
        if (T) puts("");
    }
    return 0;
}
