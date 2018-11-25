#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

#define maxn 1010
#define INF 1e30

struct Section {
    double x, c, dt;
    bool operator < (const Section &rhs) const {
        return x < rhs.x;
    }
} sec[maxn];

int n, kase;
int vis[maxn][maxn][2];
double v, x, totc;
double prec[maxn];
double d[maxn][maxn][2];

double cost(double x1, double x2, int l, int r) {
    double c = 0;
    if (l >= 0 && r >= 0)
        c = prec[r] - prec[l-1];
    return (prec[n] - c) * fabs(x1 - x2) / v;
}

/*
 double cost(double x1, double x2, int l, int r) {
    double c = 0;
    if (l >= 0 && r >= 0)
        c = prec[n] - (prec[r] - prec[l-1]);
    return c * (fabs(x1 - x2) / v);
 }
*/

double dp(int l, int r, int p) {
    if (l == 1 && r == n) return 0;
    
    double &res = d[l][r][p];
    if (vis[l][r][p] == kase) return res;
    vis[l][r][p] = kase;
    res = INF;
    
    double x = (p ? sec[r].x : sec[l].x);
    if (r < n) res = min(res, dp(l, r+1, 1) + cost(x, sec[r+1].x, l, r));
    if (l > 1) res = min(res, dp(l-1, r, 0) + cost(x, sec[l-1].x, l, r));
    return res;
}

int main() {
    memset(vis, 0, sizeof(vis));
    while (scanf("%d%lf%lf", &n, &v, &x) == 3 && n) {
        kase++; totc = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%lf%lf%lf", &sec[i].x, &sec[i].c, &sec[i].dt);
            totc += sec[i].c;
        }
        sort(sec+1, sec+1+n);
        
        prec[0] = 0;
        for (int i = 1; i <= n; i++)
            prec[i] = prec[i-1] + sec[i].dt;
        
        sec[0].x = -INF; sec[n+1].x = INF;
        double ans = INF;
        for (int i = 1; i <= n+1; i++) {
            if (sec[i-1].x < x && x < sec[i].x) {
                if (i > 1) ans = min(ans, dp(i-1, i-1, 0) + cost(x, sec[i-1].x, -1, -1));
                if (i <= n) ans = min(ans, dp(i, i, 0) + cost(x, sec[i].x, -1, -1));
                break;
            }
        }
        printf("%.0lf\n", floor(ans + totc));
    }
    return 0;
}
