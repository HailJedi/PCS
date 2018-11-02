#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int H = 1e6+5;
const int N = 1e5+5;

int lowbit(int x) {
    return x & (-x);
}

void add(int p, int v, ll *b) {
    for (; p < H; p += lowbit(p)) {
        b[p] += v;
    }
}

ll ask(int p, ll *b) {
    ll ret = 0;
    for (; p > 0; p -= lowbit(p)) {
        ret += b[p];
    }
    return ret;
}

ll ct[H], sm[H];
int h[N];
int n, k;

int midpoint() {
    int ret = 0, t = 0;
    for (int i = 20; i >= 0; i--) {
        ret += (1 << i);
        if (ret > H || t + ct[ret] >= (k+1)/2) {
            ret -= (1 << i);
        } else {
            t += ct[ret];
        }
    }
    return ret + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k;
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        h[i]++;
        if (i <= k) {
            sum += h[i];
            add(h[i], 1, ct);
            add(h[i], h[i], sm);
        }
    }
    h[n+1] = 1;
    ll ans = 1e18;
    for (int rp = k; rp <= n; rp++) {
        int mdv = midpoint();
        int lpts = ask(mdv, ct), rpts = k - lpts;
        ll lsum = ask(mdv, sm), rsum = sum - lsum;
        ans = min(ans, rsum - lsum + (lpts - rpts) * mdv);
        (sum -= h[rp-k+1]) += h[rp+1];
        add(h[rp-k+1], -1, ct), add(h[rp+1], 1, ct);
        add(h[rp-k+1], -h[rp-k+1], sm), add(h[rp+1], h[rp+1], sm);
    }
    cout << ans << endl;
    return 0;
}