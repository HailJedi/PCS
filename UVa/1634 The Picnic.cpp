#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const double eps = 1e-8;
const int maxn = 100+5;

int cmp(double x) {
    if (fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}

struct Point {
    double x, y;
    Point (double x = 0, double y = 0) : x(x), y(y) {}
} pt[maxn], p[maxn], O;

double cross(const Point &O, const Point &A, const Point &B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}
double dist(const Point &lhs, const Point &rhs) {
    return (lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y);
}
bool _cmp(const Point &lhs, const Point &rhs) {
    if (cmp(cross(O, lhs, rhs)) == 0)
        return dist(lhs, O) < dist(rhs, O); // short first
    return cmp(cross(O, lhs, rhs)) > 0; // anticlockwise
}

int idx;
double dp[maxn][maxn];

double solve() {
    double res = 0;
    for (int i = 1; i <= idx; i++) 
        for (int j = 1; j <= idx; j++)
            dp[i][j] = 0;

    for (int i = 1; i <= idx; i++) {
        int j = i-1;
        while (j >= 1 && cmp(cross(O, p[i], p[j])) == 0) j--;
        bool flag = (j == i-1);
        while (j >= 1) {
            int k = j-1;
            while (k >= 1 && cross(p[i], p[j], p[k]) > 0) k--;
            double area = fabs(cross(O, p[i], p[j]))/2;
            if (k >= 1) area += dp[j][k];
            if (flag) dp[i][j] = area;
            res = max(res, area);
            j = k;
        }
        if (flag) 
            for (int j = 2; j < i; j++)
                dp[i][j] = max(dp[i][j], dp[i][j-1]);
    }

    return res;
}

int main() {
    int T, M; 
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &M);
        for (int i = 1; i <= M; i++)
            scanf("%lf%lf", &pt[i].x, &pt[i].y);

        double ans = 0;
        for (int i = 1; i <= M; i++) {
            O = pt[i]; idx = 0;
            for (int j = 1; j <= M; j++) {
                if (pt[j].y >= O.y || (pt[j].y == O.y && pt[j].x >= O.x)) {
                    p[++idx] = pt[j];
                }
            }
            sort(p+1, p+1+idx, _cmp);
            ans = max(ans, solve());
        }
        printf("%.1lf\n", ans);
    }
    return 0;
}