#include <iostream>
#include <cstring>
#include <algorithm>
#define maxr 15
#define maxn 100
using namespace std;

int n, useful;
int G[maxr][maxr];
int d[1<<maxr];
int optim[1<<maxr];
int color[maxr];
char u[maxn], v[maxn];
bool indep[1<<maxr];

bool Separated(int set) {
    for (int i = 0; i < maxr; i++) if (set&(1<<i))
        for (int j = 0; j < maxr; j++) if (set&(1<<j))
            if (G[i][j]) return false;
    return true;
}

int DP(int set) {
    int &res = d[set];
    if (res != -1) return res;
    if (set == 0) return 0;
    res = maxr+1;
    for (int s = set; s; s = (s-1)&set)
        if (indep[s]) {
            int cmp = DP(set^s) + 1;
            if (cmp < res) { res = cmp; optim[set] = s; }
        }
    return res;
}

void Mark(int set, int col) {
    for (int i = 0; i < maxr; i++) if (set&(1<<i))
        color[i] = col;
}

int main() {
    while (scanf("%d", &n) == 1) {
        memset(G, 0, sizeof(G));
        for (int i = 0; i < n; i++) {
            cin >> u[i] >> v[i];
            int x = u[i]-'L', y = v[i]-'L';
            useful |= (1<<x); useful |= (1<<y);
            G[x][y] = G[y][x] = 1;
        }
        
        memset(indep, 0, sizeof(indep));
        for (int s = useful; s; s = (s-1)&useful)
            indep[s] = Separated(s);
        
        memset(optim, 0, sizeof(optim));
        memset(d, -1, sizeof(d));
        int ans = DP(useful)-2;
        printf("%d\n", ans);
        
        int col = 0;
        for (int s = useful; s; s ^= optim[s])
            Mark(s, col++);
        
        for (int i = 0; i < n; i++) {
            if (color[u[i]-'L'] > color[v[i]-'L']) swap(u[i], v[i]);
            printf("%c %c\n", u[i], v[i]);
        }
    }
    return 0;
}
