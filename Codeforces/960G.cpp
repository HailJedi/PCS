#include <bits/stdc++.h>

#define mp make_pair
#define fs first
#define sc second
#define sz(x) (x.size())

using namespace std;

typedef unsigned long long ull;
const ull mod = 998244353;
const int N = 400010;
int n, A, B;
typedef vector<ull> Poly;
typedef pair<ull, int> PII;
Poly poly[N];
set<PII> st;
ull fac[N], ifac[N], inv[N];

const double PI = acos(-1.0);

struct Complex {
    long double r, i;
    Complex(long double r = 0, long double i = 0) : r(r), i(i) {}
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

int l, wid = 1;
ull rev[N];

void fft(Complex *a, int t) {
    for (int i = 0; i < wid; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int stp = 1; stp < wid; stp <<= 1) {
        Complex wn(cos(PI/stp), t*sin(PI/stp));
        for (int j = 0; j < wid; j += (stp<<1)) {
            Complex w(1, 0);
            for (int k = 0; k < stp; k++) {
                Complex x = a[j+k], y = w * a[j+stp+k];
                a[j+k] = x + y;
                a[j+stp+k] = x - y;
                w = w * wn;
            }
        }
    }
}

Poly multi(Poly &A, Poly &B) {
	int n = sz(A)-1, m = sz(B)-1;
	wid = 1, l = 0;
	while (wid <= m+n) wid <<= 1, l++;
	for (int i = 0; i < wid; i++) 
		a[i].r = a[i].i = b[i].r = b[i].i = 0;
	for (int i = 0; i <= n; i++) a[i].r = A[i];
	for (int i = 0; i <= m; i++) b[i].r = B[i];
	for (int i = 0; i < wid; i++)
		rev[i] = (rev[i>>1]>>1)|((1&i)<<(l-1));
	fft(a, 1); fft(b, 1);
	for (int i = 0; i < wid; i++) a[i] = a[i] * b[i];
	fft(a, -1);
	Poly ret(m+n+1);
	for (int i = 0; i <= m+n; i++)
		ret[i] = ull(a[i].r/wid+0.5) % mod;
	return ret;
}

ull stirling_1(int k, int n) {
	if (!k && !n) return 1;
	if (!k || !n) return 0;
	for (int i = 0; i < n; i++) {
		poly[i] = Poly(2, 1);
		poly[i][0] = i;
		st.insert(mp(2, i));
	}
	while (sz(st) > 1) {
		int a = st.begin()->sc; st.erase(st.begin());
		int b = st.begin()->sc; st.erase(st.begin());
 		poly[n] = multi(poly[a], poly[b]);
		st.insert(mp(sz(poly[n]), n));
		n++;
	}
	return poly[st.begin()->sc][k] % mod;
}

ull C(int k, int n) {
	fac[0] = ifac[0] = inv[1] = 1;
	for (int i = 2; i <= n; i++)
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
	for (int i = 1; i <= n; i++) {
		fac[i] = i * fac[i - 1] % mod;
		ifac[i] = inv[i] * ifac[i - 1] % mod;
	}
	return (k >= 0 && n >= k ? fac[n] * ifac[k] % mod * ifac[n - k] % mod : 0);
}

int main() {
	cin >> n >> A >> B;
	ull c = C(A-1, A+B-2);
	ull s = stirling_1(A+B-2, n-1);
	cout << c << endl << s << endl;
	cout << s % mod * c % mod << endl;
	return 0;
}