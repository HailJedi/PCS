#include <cstdio>
#include <algorithm>
using namespace std;

struct Interval {
    int l, r;
    Interval(int l = 0, int r = 0) : l(l), r(r) {}
    bool operator < (const Interval &rhs) const {
        return r < rhs.r || (r == rhs.r && l < rhs.l);
    }
} inter[100010];

const int INF = 0x3f3f3f3f;

int main()
{
    // freopen("read.in", "r", stdin);
    // freopen("write.out", "w", stdout);
    
    int n;
    
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d%d", &inter[i].l, &inter[i].r);
        sort(inter, inter+n);
        
        int cl = -INF, cr = INF, ans = 0;
        for (int i = 0; i < n; i++) {
            cl = max(cl+1, inter[i].l);
            cr = min(cr+1, inter[i].r);
            if (cr <= cl) { ans++; cl = inter[i].l; cr = inter[i].r; }
        }
        printf("%d\n", ans);
    }
    return 0;
}

