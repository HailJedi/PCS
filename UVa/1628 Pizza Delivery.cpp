#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define maxn 100 + 5
int rpos[maxn], pay[maxn];
int d[maxn][maxn][maxn][2];
int vis[maxn][maxn][maxn][2];
int n, kase;

void read() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> rpos[i];
    for (int i = 1; i <= n; i++)
        cin >> pay[i];
}

int dp(int l, int r, int togo, int pos) {
    if (togo == 0) return 0;
    int &ans = d[l][r][togo][pos];
    if (vis[l][r][togo][pos] == kase) return ans;
    vis[l][r][togo][pos] = kase;
    ans = 0;
    if (pos) { // currently at r
        for (int i = 1; i < l; i++)
            ans = max(ans, dp(i, r, togo-1, 0) + pay[i] - togo*abs(rpos[r]-rpos[i]));
        for (int i = r+1; i <= n; i++)
            ans = max(ans, dp(l, i, togo-1, 1) + pay[i] - togo*abs(rpos[i]-rpos[r]));
    } else { // currently at l
        for (int i = 1; i < l; i++)
            ans = max(ans, dp(i, r, togo-1, 0) + pay[i] - togo*abs(rpos[l]-rpos[i]));
        for (int i = r+1; i <= n; i++)
            ans = max(ans, dp(l, i, togo-1, 1) + pay[i] - togo*abs(rpos[l]-rpos[i]));
    }
    return ans;
}

void solve() {
    int ans = 0;
    for (int togo = 1; togo <= n; togo++)
        for (int i = 1; i <= n; i++)
            ans = max(ans, dp(i, i, togo-1, 0) + pay[i] - togo * abs(rpos[i]));
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        kase++;
        read();
        solve();
    }
    return 0;
}
