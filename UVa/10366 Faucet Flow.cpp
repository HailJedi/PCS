#include <cstdio>
#include <map>
#include <algorithm>
#include <map>
using namespace std;

typedef long long ll;

map<ll, ll> height;

int main() {
//    freopen("write.txt", "w", stdout);
    ll lx, rx, maxl, maxr, maxlp = 0, maxrp = 0;
    while (scanf("%lld%lld", &lx, &rx) == 2 && lx && rx) {
//        puts("Case");
        maxl = maxr = -1;
        for (ll i = lx; i <= rx; i += 2) {
            scanf("%lld", &height[i]); height[i] *= 2;
            if (i <= -1 && maxl <= height[i]) { maxl = height[i]; maxlp = i; }
            if (i >= 1 && maxr < height[i]) { maxr = height[i]; maxrp = i; }
        }
        ll ans = 1000000000000000;
        
        if (maxl >= maxr) { // overflow at right
            ll h = 0, mw = 0, sw = 0, water, i;
            for (i = maxrp; i > lx && (i == maxrp || maxr > height[i]); i-=2) mw += maxr;
            for (ll j = rx; j != maxrp; j -= 2) { h = max(h, height[j]); sw += h; }
            if (height[i] == maxr) {
//                printf("%d \n", i);
                ll sw2 = 0;
                for (ll j = i; j > lx && height[j] <= maxr; j -= 2) sw2 += maxr;
                if (sw2 >= sw) water = mw + 2 * sw;
                else water = mw + sw + sw2;
//                printf("%d %d %d\n", sw, sw2, mw);
            } else water = mw + sw;
            ans = min(ans, water);
        }
//        printf("%d\n", ans);
        if (maxl <= maxr) { // overflow at left
            ll h = 0, mw = 0, sw = 0, water, i;
            for (i = maxlp; i < rx && (i == maxlp || maxl > height[i]); i+=2) mw += maxl;
            for (ll j = lx; j != maxlp; j += 2) { h = max(h, height[j]); sw += h; }
            if (height[i] == maxl) {
//                printf("%d ", i);
                ll sw2 = 0;
                for (ll j = i; j < rx && height[j] <= maxl; j += 2) sw2 += maxl;
                if (sw2 >= sw) water = mw + 2 * sw;
                else water = mw + sw + sw2;
//                printf("%d %d %d\n", sw, sw2, mw);
            } else water = mw + sw;
            ans = min(ans, water);
        }
        
        printf("%lld\n", ans);
    }
    return 0;
}
