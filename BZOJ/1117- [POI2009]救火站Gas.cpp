#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 1e5+5;
const int K = 20+5;
ll need[N][K], cover[N][K];
vector<int> g[N];
int n, k, s, u, v;
ll ans;

void elimilate(int u, bool ok = false) {
    for (int i = 0; i <= k; i++) {
        for (int j = i; j >= 0 && (ok || j >= i-1); j--) {
            ll elim = min(cover[u][i], need[u][j]);
            cover[u][i] -= elim;
            need[u][j] -= elim;
            if (!cover[u][i]) {
                break;
            }
        }
    }
}

void dfs(int u, int f) {
    need[u][0] = 1;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v != f) {
            dfs(v, u);
            for (int i = 1; i <= k; i++) {
                need[u][i] += need[v][i-1];
                cover[u][i-1] += cover[v][i];
            }
        }
    }
    if (need[u][k] > 0) {
        ll cov = (need[u][k] + s - 1) / s;
        cover[u][k] += cov * s;
        ans += cov;
    }
    elimilate(u);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> s >> k;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    } 
    dfs(1, 0);
    elimilate(1, true);
    ll t = 0;
    for (int i = 0; i <= k; i++) {
        t += need[1][i];
    }
    ans += (t + s - 1) / s;
    cout << ans << endl;
    return 0;
}