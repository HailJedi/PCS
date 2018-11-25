#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iomanip>
#define maxn 10000000
using namespace std;

struct Interval {
    double l, r;
    Interval(double l = 0, double r = 0) : l(l), r(r) {}
    bool operator < (const Interval &rhs) const {
        return r < rhs.r || (r == rhs.r && l > rhs.l);
    }
} inter[maxn];

long long n;
double L, D;
double X[maxn], Y[maxn];

void create() {
    for (int i = 0; i < n; i++) {
        const double x = X[i], y = Y[i];
        double l, r, d;
        d = sqrt(D*D-y*y);
        l = (x - d >= 0 ? x - d : 0);
        r = (x + d <= L ? x + d : L);
        inter[i] = Interval(l, r);
    }
}

int done[maxn];
void solve() {
    memset(done, 0, sizeof(done));
    sort(inter, inter+n);
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (done[i]) continue;
        done[i] = 1; ans++;
        double cur = inter[i].r;
        int iter = i + 1;
        while (iter < n && inter[iter].l <= cur
               && cur <= inter[iter].r) done[iter++] = 1;
    }
    cout << ans << endl;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    
    ios::sync_with_stdio(false);
    
    while (cin >> L && L != EOF) {
        cin >> D >> n;
        
        for (int i = 0; i < n; i++)
            cin >> X[i] >> Y[i];
        
        create();
        solve();
    }
    return 0;
}

