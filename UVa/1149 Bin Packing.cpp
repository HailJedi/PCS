#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 100010;
int n, L;
int l[maxn];
int taken[maxn];

int solve() {
    int ans = 0;
    sort(l, l+n);
    memset(taken, 0, sizeof(taken));
    for (int i = 0; i < n; i++) {
        if (taken[i]) continue;
        ans++;
        int iter = upper_bound(l, l+n, L-l[i]) - l; iter--;
        while (iter > i && taken[iter]) iter--;
        if (iter >= 0) taken[iter] = 1;
    }
    return ans;
}

int main() {
//    freopen("result.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> n >> L;
        for (int i = 0; i < n; i++) cin >> l[i];
        cout << solve() << endl;
        if (T) cout << endl;
    }
    return 0;
}

