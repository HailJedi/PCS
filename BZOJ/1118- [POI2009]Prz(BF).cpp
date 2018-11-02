#include <bits/stdc++.h>

using namespace std;

const int K = 100+5;
const int N = 1e5+5;
bool dp[N][K];
int x[N], y[N], cnt[K];
int n, m, t, mo, tag;

bool solve(int d, int l1, int r1, int l2, int r2) {
    if (dp[l1][d]) {
        return true;
    }
    if (l1 == r1) {
        return dp[l1][d] = x[l1] == y[l2];
    }
    int ct = 0, p1 = 0, p2 = 0;
    tag++;
    for (int i = l1; i <= r1; i++) {
        if (cnt[x[i]] != tag) {
            cnt[x[i]] = tag;
            ct++;
        }
        if (ct == mo - d + 1) {
            p1 = i - 1;
            break;
        }
    }
    tag++;
    ct = 0;
    for (int i = l2; i <= r2; i++) {
        if (cnt[y[i]] != tag) {
            cnt[y[i]] = tag;
            ct++;
        }
        if (ct == mo - d + 1) {
            p2 = i - 1;
            break;
        }
    }
    if (!solve(d+1, l1, p1, l2, p2)) {
        return false;
    }
    tag++;
    ct = 0;
    for (int i = r1; i >= l1; i--) {
        if (cnt[x[i]] != tag) {
            cnt[x[i]] = tag;
            ct++;
        }
        if (ct == mo - d + 1) {
            p1 = i + 1;
            break;
        }
    }
    tag++;
    ct = 0;
    for (int i = r2; i >= l2; i--) {
        if (cnt[y[i]] != tag) {
            cnt[y[i]] = tag;
            ct++;
        }
        if (ct == mo -  d + 1) {
            p2 = i + 1;
            break;
        }
    }
    if (!solve(d+1, p1, r1, p2, r2)) {
        return false;
    }
    return dp[l1][d] = true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while (t--) {
        cin >> n >> m;
        int it = 0;
        for (int i = 1; i <= n; i++) {
            cin >> x[++it];
            while (x[it] == x[it-1]) {
                it--;
            }
        }
        n = it;
        it = 0;
        for (int i = 1; i <= m; i++) {
            cin >> y[++it];
            while (y[it] == y[it-1]) {
                it--;
            }
        }
        m = it;
        bool ok = true;
        memset(cnt, 0, sizeof(cnt));
        mo = 0;
        for (int i = 1; i <= n; i++) {
            cnt[x[i]] = 1;
        }
        for (int i = 1; i <= m && ok; i++) {
            if (!cnt[y[i]]) {
                ok = false;
            } else 
            if (cnt[y[i]] == 1) {
                cnt[y[i]] = 2;
                mo++;
            }
        }
        for (int i = 0; i < K && ok; i++) {
            if (cnt[i] == 1) {
                ok = false;
            }
        }
        if (!ok) {
            cout << 0 << endl;
        } else {
            memset(dp, false, sizeof(dp));  
            tag = 0;
            cout << solve(1, 1, n, 1, m) << endl;
        }
    }
    return 0;
}