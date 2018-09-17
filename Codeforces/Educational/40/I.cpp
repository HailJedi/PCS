#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()

using namespace std;

const int N = 125000<<2;
const double PI = acos(-1.0);

struct Complex {
    double r, i;
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

int n, m, l, wid = 1;
int rev[N];

void fft(vector<Complex> &a, int t) {
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

char s[N], t[N];
int r[N][6];

int root(int x, int y) {
    return y == r[x][y] ? y : r[x][y] = root(x, r[x][y]);
}

vector<Complex> vec1[6], vec2[6];

int main() {
    scanf("%s %s", s, t);
    n = strlen(s), m = strlen(t);

    while (wid <= n+m) wid <<= 1, l++;
    for (int i = 0; i < wid; i++) 
        rev[i] = (rev[i>>1]>>1)|((1&i)<<(l-1));

    for (int i = 0; i <= n-m; i++) 
        for (int j = 0; j < 6; j++) r[i][j] = j;

    for (int i = 0; i < 6; i++) {
        vector<int> vec(N, 0);
        for (int j = 0; j < n; j++)
            if (s[j] == 'a' + i) vec[j] = 1;
        vector<Complex> v(N, 0);
        for (int j = 0; j < n; j++) v[j].r = vec[j];
        fft(v, 1);
        vec1[i] = v;
    }
    for (int i = 0; i < 6; i++) {
        vector<int> vec(N, 0);
        for (int j = 0; j < m; j++)
            if (t[j] == 'a' + i) vec[m-1-j] = 1;
        vector<Complex> v(N, 0);
        for (int j = 0; j < m; j++) v[j].r = vec[j];
        fft(v, 1);
        vec2[i] = v;
    }
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            vector<Complex> vec(N);
            for (int k = 0; k < N; k++) vec[k] = vec1[i][k] * vec2[j][k];
            fft(vec, -1);
            for (int k = 0; k <= n-m; k++) {
                int t = ((int)(vec[k+m-1].r + (vec[k+m-1].r > 0 ? 0.5 : -0.5)));
                if (t == 0) continue;
                // puts("?");
                r[k][root(k, i)] = root(k, j);
            }
        }

    for (int i = 0; i <= n-m; i++) {
        int ans = 6;
        for (int j = 0; j < 6; j++) 
            if (r[i][j] == j) ans--;
        printf("%d ", ans);
    }

    return 0;
}