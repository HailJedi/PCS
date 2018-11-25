#include <cstdio>
#include <algorithm>
#include <cstring>
#define maxb 300
using namespace std;

int blocks[maxb][3], d[maxb][3];
int n, ans;

bool read() {
    scanf("%d", &n);
    if (n == 0) return false;
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &blocks[i][0], &blocks[i][1], &blocks[i][2]);
        sort(blocks[i], blocks[i]+3);
    }
    return true;
}

void get_dimension(int *dim, int blk, int stat) {
    int cnt = 0;
    for (int i = 0; i < 3; i++)
        if (i != stat) dim[cnt++] = blocks[blk][i];
}

int dp(int blk, int stat) {
    int &res = d[blk][stat];
    if (res > 0) return res;
    res = 0;
    int dim[2], dim2[2];
    get_dimension(dim, blk, stat);
    for (int b = 0; b < n; b++)
        for (int st = 0; st < 3; st++) {
            get_dimension(dim2, b, st);
            if (dim2[0] < dim[0] && dim2[1] < dim[1])
                res = max(res, dp(b, st));
        }
    res += blocks[blk][stat];
    return res;
}

void solve() {
    ans = -1; memset(d, -1, sizeof(d));
    for (int bl = 0; bl < n; bl++)
        for (int st = 0; st < 3; st++)
            ans = max(ans, dp(bl, st));
}

void print(int kase) {
    printf("Case %d: maximum height = %d\n", kase, ans);
}

int main() {
    for (int kase = 1; ; kase++) {
        if (!read()) break;
        solve();
        print(kase);
    }
    return 0;
}
