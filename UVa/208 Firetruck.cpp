#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 21;
int fire;
int street[maxn][maxn];
int id[maxn];
int ans[maxn];
int cnt;
int vis[maxn];

void output(int d) {
    for (int i = 0; i < d; i++) {
        printf("%d ", ans[i]);
    } printf("%d\n", ans[d]);
}

void solve(int cur, int d) {
    ans[d] = cur;
    if (cur == fire) {
        output(d);
        cnt++;
        return;
    }
    for (int next = 0; next < id[cur]; next++) if (street[cur][next] && !vis[street[cur][next]]) {
        vis[street[cur][next]] = 1;
        solve(street[cur][next], d+1);
        vis[street[cur][next]] = 0;
    }
}

int pa[maxn];
int find(int x) { return x == pa[x] ? x : find(pa[x]); }
void unite(int x, int y) { int f1 = find(x), f2 = find(y); pa[f1] = f2; }
bool same(int x, int y) { return find(x) == find(y); }
void init_set() { for (int i = 1; i < maxn; i++) pa[i] = i; }
int main() {
    int kase = 1;
    while (scanf("%d", &fire) == 1) {
        memset(street, 0, sizeof(street));
        memset(id, 0, sizeof(id));
        init_set();
        int cor1, cor2;
        while (scanf("%d%d", &cor1, &cor2) == 2 && cor1 && cor2) {
            street[cor1][id[cor1]++] = cor2;
            street[cor2][id[cor2]++] = cor1;
            unite(cor1, cor2);
        }
        cnt = 0;
        for (int i = 0; i < maxn; i++) { sort(street[i], street[i]+id[i]); }
        printf("CASE %d:\n", kase++);
        if(same(1, fire)) { vis[1] = 1; solve(1, 0); }
        printf("There are %d routes from the firestation to streetcorner %d.\n", cnt, fire);
    }
    return 0;
}
