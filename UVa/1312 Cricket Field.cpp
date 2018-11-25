#include <cstdio>
#include <algorithm>
using namespace std;

const int maxp = 101;

struct Point {
    int x, y;
    bool operator < (const Point &rhs) const {
        return x < rhs.x || x == rhs.x && y < rhs.y;
    }
} p[maxp];

int N, W, H;
int h[maxp];

int main()
{    
    int T; scanf("%d", &T);
    bool first = true;
    while (T--) {
        if (!first) puts("");
        else first = false;
        
        scanf("%d%d%d", &N, &W, &H);
        
        for (int i = 1; i <= N; i++) {
            scanf("%d%d", &p[i].x, &p[i].y);
            h[i] = p[i].y;
        } h[0] = 0, h[N+1] = H;
        sort(p+1, p+1+N);
        sort(h, h+N+2);
        
        int ans = -1, ansx = 0, ansy = 0;
        for (int i = 0; i <= N+1; i++) {
            for(int j = i+1; j <= N+1; j++) {
                if (h[i] == h[j]) continue;
                int r = h[j] - h[i];
                int lst = 0;
                for (int k = 1; k <= N; k++) {
                    if (!(h[i] < p[k].y && p[k].y < h[j])) continue;
                    if (p[k].x == lst) continue;
                    if (min(p[k].x-lst, r) > ans) {
                        ans = min(p[k].x-lst, r);
                        ansx = lst; ansy = h[i];
                    }
                    lst = p[k].x;
                }
                if (min(W-lst, r) > ans) {
                    ans = min(W-lst, r);
                    ansx = lst, ansy = h[i];
                }
            }
        }
        printf("%d %d %d\n", ansx, ansy, ans);
    }
    return 0;
}

