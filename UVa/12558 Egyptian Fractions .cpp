#include <iostream>
#include <set>
#include <cstring>
using namespace std;

typedef long long ll;

ll restr[5];
int maxd;
int kase = 0;
ll ans[15];
ll temp[15];

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a%b);
}

bool try_update() {
    for (int i = maxd; i >= 1; i--)
        if (ans[i] != temp[i])
            return temp[i] < ans[i] || ans[i] == -1;
    return false;
}

ll get_min(ll a, ll b) {
    return b / a;
}

bool dfs(int d, ll a, ll b, ll p) {
    if (d == maxd) {
        bool mark = false;
        for (int i = 0; i <= 4; i++)
            if (b == restr[i]) { mark = true; break; }
        if (b % a != 0 || mark) return false;
        temp[d] = b;
        if (try_update())
            memcpy(ans, temp, sizeof(temp));
        return true;
    }
    
    bool update = false;
    p = max(p, get_min(a, b));
    for (ll s = p + 1; ; s++) {
        bool mark = false;
        for (int i = 0; i <= 4; i++)
            if (s == restr[i]) { mark = true; break; }
        if (mark) continue;
        if (a * s >= b * ll(maxd - d + 1)) return update;
        ll na =  a * s - b, nb = b * s;
        ll g = gcd(na, nb);
        na /= g; nb /= g;
        temp[d] = s;
        if (dfs(d+1, na, nb, s)) update = true;
    }
    
    return update;
}

void solve(ll a, ll b) {
    for (maxd = 1; ; maxd++) {
        memset(ans, -1, sizeof(ans));
        if(dfs(1, a, b, 1)) break;
    }
    
    cout << "Case " << ++kase << ": " << a << '/' << b << "=";
    for (int i = 1; i < maxd; i++) {
        cout << "1/" << ans[i] << '+';
    } cout << "1/" << ans[maxd] << endl;
}

void debug() {
    cout << gcd(105, 34) << endl;
}

int main() {
    
    //debug();
    
    int T, k;
    ll a, b;
    cin >> T;
    while (T--) {
        cin >> a >> b >> k;
        memset(restr, 0, sizeof(restr));
        while (k--) {
            cin >> restr[k];
        }
        solve(a, b);
    }
}