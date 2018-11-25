#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define maxn 500+10
#define INF 0x3f3f3f3f
#define width(x, y) (abs(x-y)+1)
using namespace std;

int a, b, r, c;
int depth[maxn][maxn];
int minc[maxn];

long long height(int wr, int wc, int dpth) {
    if (dpth == 0) return 0;
    int base = dpth * wr * wc;
    int res = base / (r * c - wc * wr);
    if (base % (r * c - wc * wr) == 0) res--;
    return res + dpth;
}

int main() {
    while (scanf("%d%d%d%d", &a, &b, &r, &c) == 4) {
        for (int rr = 1; rr <= r; rr++)
            for (int cc = 1; cc <= c; cc++)
                scanf("%d", &depth[rr][cc]);
        long long ans = 0;
        if (a < b) swap(a, b); // make a >= b
        for (int tr = 1; tr <= r; tr++) {// top row index
            for (int cc = 1; cc <= c; cc++) minc[cc] = INF;
            for (int br = tr; br <= r; br++) { // bottom row index
                if (width(br, tr) > a) break;
                for (int tc = 1; tc <= c; tc++) { // top column index
                    int dpth = INF;
                    for (int bc = tc; bc <= c; bc++) { // bottom column index
                        if (width(tc, bc) > a) break;
                        minc[bc] = min(minc[bc], depth[br][bc]);
                        dpth = min(dpth, minc[bc]);
                        int wth_r = width(br, tr);
                        int wth_c = width(bc, tc);
                        if (wth_c < wth_r) swap(wth_c, wth_r); // make wth_c >= wth_r
                        if (a >= wth_c && b >= wth_r)
                            ans = max(ans, height(wth_r, wth_c, dpth) * wth_r * wth_c);
                    }
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}



