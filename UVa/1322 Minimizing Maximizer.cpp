#include <cstdio>
#include <algorithm>
using namespace std;

const int maxm = 500000+5;
const int INF = 1e9;

int BIT[maxm];

int query(int x) {
    int res = INF;
    while (x) {
        res = min(res, BIT[x]);
        x -= x&(-x);
    }
    return res;
}

void modify(int d, int x, int L) {
    while (x <= L) {
        BIT[x] = min(BIT[x], d);
        x += x&(-x);
    }
}

int main() {
    int N, M, T, x, y;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &N, &M);
        for (int i = 0; i <= N; i++) 
            BIT[i] = INF;
        modify(0, N, N);
        while (M--) {
            scanf("%d%d", &x, &y);
            int val = query(N+1-x) + 1;
            modify(val, N+1-y, N);
        }
        printf("%d\n", query(1));
        if (T) puts("");
    }
    return 0;
}