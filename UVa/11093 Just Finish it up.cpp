#include <iostream>
#include <cstdio>
using namespace std;

const int maxn = 100010;
int n, p[maxn], q[maxn];

int go(int s) {
    int fuel = p[s] - q[s];
    for (int i = (s+1)%n; i != s; i = (i+1)%n) {
        if (fuel < 0) return i;
        fuel += p[i] - q[i];
    }
    if (fuel < 0) return -1;
    return s;
}

int solve() {
    int start = 0;
    while (true) {
        int finish = go(start);
        if (finish < start) return -1;
        if (finish == start) return finish;
        start = finish;
    }
}

int main() {
//    freopen("input.in", "r", stdin);
//    freopen("output.out", "w", stdout);

    int T; cin >> T;
    for (int kase = 1; kase <= T; kase++) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> p[i];
        for (int i = 0; i < n; i++) cin >> q[i];
        int ans = solve();

        cout << "Case " << kase << ": ";
        if (ans < 0) cout << "Not possible\n";
        else cout << "Possible from station " << ans + 1 << endl;
    }
    return 0;
}
