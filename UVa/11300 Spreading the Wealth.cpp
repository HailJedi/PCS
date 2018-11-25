#include <iostream>
#include <cmath>
#include <algorithm>
#define abs(x) ((x) > 0 ? (x) : -(x))
using namespace std;

const int maxn = 1000000 + 10;
int n;
long long ave, c[maxn], b[maxn];

void solve() {
    ave /= n;
    b[0] = 0;
    for (int i = 1; i < n; i++) {
        b[i] = b[i-1] + c[i] - ave;
    } sort(b, b+n);
    long long x1 = b[n/2], ans = 0;
    for (int i = 0; i < n; i++) {
        ans += abs(x1-b[i]);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n && n) {
        ave = 0;
        for (int i = 1; i <= n; i++) {
            cin >> c[i];
            ave += c[i];
        }
        solve();
    }
    return 0;
    
}
