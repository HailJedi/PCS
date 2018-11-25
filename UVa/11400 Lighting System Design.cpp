#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 1000+5
using namespace std;

struct Bulb {
    int v, k, c, l; // voltage, source, bulb, required
    Bulb(int v = 0, int k = 0, int c = 0, int l = 0) : v(v), k(k), c(c), l(l) {}
    bool operator < (const Bulb &rhs) const {
        return v < rhs.v;
    }
} bulb[maxn];
int dp[maxn], s[maxn];
int n;

int main() {
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 1; i <= n; i++)
            scanf("%d%d%d%d", &bulb[i].v, &bulb[i].k, &bulb[i].c, &bulb[i].l);
        sort(bulb+1, bulb+n+1);
        
        s[0] = 0;
        for (int i = 1; i <= n; i++) s[i] = s[i-1] + bulb[i].l;
        
//        dp[0] = 0;
//        for (int i = 1; i <= n; i++)
//            dp[i] = dp[i-1] + bulb[i].l * bulb[i].c + bulb[i].k;
        
        for (int i = 1; i <= n; i++) {
            dp[i] = bulb[i].c * s[i] + bulb[i].k;
            for (int j = 1; j <= i-1; j++)
                dp[i] = min(dp[i], dp[j] + (s[i] - s[j]) * bulb[i].c + bulb[i].k);
        }
        
        printf("%d\n", dp[n]);
    }
}
