#include <cstdio>
#include <vector>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 100 + 5;
const int maxr = 50 + 5;
char pattern[maxn][maxn];
vector< pair<int, int> > preProc[maxr];
int circles[maxr];
const double eps = 1e-6;

const double dx[] = {+1, +0, -1, -1, -1, +0, +1, +1};
const double dy[] = {+1, +1, +1, +0, -1, -1, -1, +0};
void init(int r) {
    double cx = r, cy = r;
    circles[r] = 0;
    for (int x = 0; x <= 2 * r; x++) {
        for (int y = 0; y <= 2 * r; y++) {
            bool in = 0, out = 0;
            for (int i = 0; i < 8; i++) {
                double nx = x + dx[i]/2, ny = y + dy[i]/2;
                if (pow(cx - nx, 2) + pow(cy - ny, 2) < r * r - eps) in = 1;
                if (pow(cx - nx, 2) + pow(cy - ny, 2) > r * r - eps) out = 1;
            }
            if (in&out) {
                circles[r]++;
                preProc[r].push_back(make_pair(x, y));
            }
        }
    }
}

struct Point {
    int r, x, y;
    Point(int r, int x, int y) : r(r), x(x), y(y) {}
    bool operator < (const Point &rhs) const {
        if (rhs.r != r) return r < rhs.r;
        if (rhs.x != x) return x < rhs.x;
        return y < rhs.y;
    }
};
vector<Point> ans;


int main() {
//    freopen("write.txt", "w", stdout);
    
    for (int r = 5; r < maxr; r++)
        init(r);
    
    int w, h, T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; kase++) {
        scanf("%d%d", &w, &h);
        for (int i = 0; i < h; i++)
            scanf("%s", pattern[i]);
        
        ans.clear();
        for (int r = 5; r <= min(w, h); r++) {
            for (int x = 0; x <= h-(2*r+1); x++) {
                for (int y = 0; y <= w-(2*r+1); y++) {
                    int cnt = 0, px = 0, py = 0;
                    for (int i = 0; i < preProc[r].size(); i++) {
                        px = preProc[r][i].first;
                        py = preProc[r][i].second;
                        if (pattern[x+px][y+py] == '1') cnt++;
                    }
                    if (cnt >= 0.7 * circles[r])
                        ans.push_back(Point(r, x+r, y+r));
                }
            }
        }
        
        printf("Case %d: %d", kase, (int)ans.size());
        sort(ans.begin(), ans.end());
        for (int i = 0; i < ans.size(); i++)
            printf(" (%d,%d,%d)", ans[i].r, ans[i].y, ans[i].x);
        puts("");
    }
    return 0;
}
