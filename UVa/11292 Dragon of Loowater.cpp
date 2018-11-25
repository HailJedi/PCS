#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 20000 + 10;
int n, m;
int d[maxn], h[maxn];

void solve() {
    sort(d+1, d+1+n);
    sort(h+1, h+1+m);
    int c = 0, cnt = 1;
    for (int i = 1; i <= m; i++) {
        if (h[i] < d[cnt]) continue;
        cnt++;
        c += h[i];
        if(cnt == n+1) break;
    }
    if (cnt <= n) cout << "Loowater is doomed!" << endl;//printf("Loowater is doomed!\n");//
    else cout << c << endl;//printf("%d\n", c);
    
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m && n && m) {
        for (int i = 1; i <= n; i++) cin >> d[i];
        for (int i = 1; i <= m; i++) cin >> h[i];
        solve();
    }
    return 0;
}
