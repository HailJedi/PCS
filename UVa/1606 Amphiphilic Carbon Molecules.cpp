#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1000 + 5;

struct Point {
    int x, y;
    double rad;
    bool operator < (const Point &rhs) const {
        return rad < rhs.rad;
    }
} abs_pos[maxn], rlt_pos[maxn];

int n, color[maxn];

bool left (Point A, Point B) {
    return B.x * A.y - B.y * A.x >= 0;
}

int solve() {
    if (n <= 2) return 2;
    int ans = 0;
    
    for (int pivot = 0; pivot < n; pivot++) {
        int tot =  0;
        
        for (int p = 0; p < n; p++) {
            if (p == pivot) continue;
            rlt_pos[tot].x = abs_pos[p].x - abs_pos[pivot].x;
            rlt_pos[tot].y = abs_pos[p].y - abs_pos[pivot].y;
            if (color[p] == 1) { rlt_pos[tot].x = -rlt_pos[tot].x; rlt_pos[tot].y = - rlt_pos[tot].y; }
            rlt_pos[tot].rad = atan2(rlt_pos[tot].y, rlt_pos[tot].x);
            tot++;
        }
        sort(rlt_pos, rlt_pos+tot);
        
        int L = 0, R = 0, cnt = 2;
        while (R < tot) {
            if (L == R) { L = (L+1)%tot; cnt++; }
            while (L != R && left(rlt_pos[L], rlt_pos[R])) { L = (L+1)%tot; cnt++; }
            cnt--;
            R++;
            ans = max(ans, cnt);
        }
    }
    
    return ans;
}

int main() {
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++)
            scanf("%d%d%d", &abs_pos[i].x, &abs_pos[i].y, &color[i]);
        printf("%d\n", solve());
    }
    return 0;
}

