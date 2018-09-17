#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define sz(x) (x.size())
#define sc second

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<ll> VI;
typedef pair<ll, ll> PII;

const int N = 1001000;
const ld PI = acos(-1.0);
const ll mod = 1009;

struct Complex {
    ld r, i;
    Complex(double r = 0, double i = 0) : r(r), i(i) {}
    Complex operator + (const Complex &a) const {
        return Complex(r+a.r, i+a.i);
    }
    Complex operator - (const Complex &a) const {
        return Complex(r-a.r, i-a.i);
    }
    Complex operator * (const Complex &a) const {
        return Complex(r*a.r-i*a.i, r*a.i+i*a.r);
    }
} a[N], b[N];

ll l, wid;
ll rev[N];

void fft(Complex *a, int t) {
    for (ll i = 0; i < wid; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (ll stp = 1; stp < wid; stp <<= 1) {
        Complex wn(cos(PI/stp), t*sin(PI/stp));
        for (ll j = 0; j < wid; j += (stp<<1)) {
            Complex w(1, 0);
            for (ll k = 0; k < stp; k++) {
                Complex x = a[j+k], y = w * a[j+stp+k];
                a[j+k] = x + y;
                a[j+stp+k] = x - y;
                w = w * wn;
            }
        }
    }
}

VI mul(VI &A, VI &B) {
    ll n = A.size()-1, m = B.size()-1;
    wid = 1, l = 0;
    while (wid <= n+m) wid <<= 1, l++;
    for (int i = 0; i < wid; i++) 
        a[i].r = a[i].i = b[i].r = b[i].i = 0;
    for (int i = 0; i <= n; i++) a[i].r = A[i];
    for (int i = 0; i <= m; i++) b[i].r = B[i];
    for (int i = 0; i < wid; i++) 
        rev[i] = (rev[i>>1]>>1)|((1&i)<<(l-1));
    fft(a, 1); fft(b, 1);
    for (int i = 0; i < wid; i++) a[i] = a[i] * b[i];
    fft(a, -1);
    VI ret(n+m+1, 0);
    for (int i = 0; i <= n+m; i++) ret[i] = ll(a[i].r/wid+0.5) % mod;
    return ret;
}

int cnt[N];
int n, m, k, x;
VI poly[N];
set<PII> st;
VI A, B, ans;

int main() {    
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x); x--;
        cnt[x]++;
    }
    for (int i = 0; i < m; i++) {
        if (cnt[i]) {
            poly[i] = VI(cnt[i]+1, 1);
            st.insert(mp(cnt[i]+1, i));
        }
    }
    while (sz(st) > 1) {
        int u = st.begin()->sc; st.erase(st.begin());
        int v = st.begin()->sc; st.erase(st.begin());
        poly[m] = mul(poly[u], poly[v]);
        st.insert(mp(sz(poly[m]), m));
        m++;
    }
    printf("%lld\n", poly[st.begin()->sc][k]);

    return 0;
}