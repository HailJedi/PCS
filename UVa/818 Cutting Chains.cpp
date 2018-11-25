#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 20;
int G[maxn][maxn];
int n, kase;
int id[maxn];
int connection[maxn][maxn];

void connect(int x, int y) {
    if (!connection[x][y]) {
        connection[x][y] = connection[y][x] = 1;
        G[x][id[x]++] = y;
        G[y][id[y]++] = x;
    }
}

int cut[maxn];
int mark[maxn];

void mark_rings(int u, int fa) {
    mark[u] = 1;
    for (int i = 0; i < id[u]; i++) if(!cut[G[u][i]] && G[u][i] != fa) {
        mark_rings(G[u][i], u);
    }
}

bool does_not_meet_condition(int number_of_cuts) {
    // exist a ring connect with more than two other rings
    int cnt[maxn]; memset(cnt, 0, sizeof(cnt));
    bool must_contains_circle = true;
    for (int ring = 1; ring <= n; ring++) if (!cut[ring]) {
        for (int i = 0; i < id[ring]; i++) {
            if (!cut[G[ring][i]]) { cnt[ring]++; }
        }
        if (cnt[ring] > 2) return true;
        if (cnt[ring] <= 1) must_contains_circle = false;
    }
    if (must_contains_circle) { return true; } // a chain without a ring connect with only one another ring is certainly a circle
    
    int number_of_subchains = 0;
    memset(mark, 0, sizeof(mark));
    for (int ring = 1; ring <= n; ring++) if (!cut[ring] && !mark[ring] && cnt[ring] <= 1) {
        // mark all rings connect with an 'end'
        mark_rings(ring, 0);
        number_of_subchains++;
    }
    for (int ring = 1; ring <= n; ring++) if (!cut[ring] && !mark[ring]) return true; // an unmarked ring implies a circle
    
    // number of chains greater than number of cuts plus one
    return number_of_subchains > number_of_cuts+1;
}

int cr[maxn+1][184756][maxn];
int cm[maxn+1];

void solve_2_0() {
    for (int maxd = 0; ; maxd++) {
        for (int i = 0; i < cm[maxd]; i++) {
            memcpy(cut, cr[maxd][i], sizeof(cut));
            if (does_not_meet_condition(maxd)) continue;
            cout << "Set " << ++kase << ": Minimum links to open is " << maxd << endl;
            return;
        }
    }
}

void solve() {
    int ans = 20;
    for (int select = 0; select < (1<<n); select++) {
        int cnt = 0;
        memset(cut, 0, sizeof(cut));
        for (int i = 0; i < n; i++) {
            if ((1<<i)&select) { // cut number (i+1)
                cut[i+1] = 1;
                cnt++;
            }
        }
        if (does_not_meet_condition(cnt)) continue;
        ans = min(ans, cnt);
    }
    cout << "Set " << ++kase << ": Minimum links to open is " << ans << endl;
}

void init() {
    for (int i = 1; i <= n; i++) memset(G[i], 0, sizeof(G[i]));
    memset(id, 0, sizeof(id));
    memset(connection, 0, sizeof(connection));
}

void Init() {
    memset(cm, 0, sizeof(cm));
    memset(cr, 0, sizeof(cr));
    for (int select = 0; select < (1<<maxn); select++) {
        int c[maxn]; memset(c, 0, sizeof(c));
        int cnt = 0;
        for (int i = 0; i < maxn; i++) if (select&(1<<i)) {
            c[i] = 1;
            cnt++;
        }
        memcpy(cr[cnt][cm[cnt]], c, sizeof(c)); cm[cnt]++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    
    Init();
    
    while (cin >> n && n) {
        init();
        int x, y;
        while (cin >> x >> y && x != -1 && y != -1) connect(x, y);
        solve_2_0();
    }
    
    return 0;
}
