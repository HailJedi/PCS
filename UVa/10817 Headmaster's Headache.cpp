#include <iostream>
#include <sstream>
#include <cstring>
#define maxs 8
#define maxn 120
#define INF 1000000000
using namespace std;

int c[maxn], st[maxn], d[maxn][1<<maxs][1<<maxs];
int s, m, n;

int dp(int t, int s0, int s1, int s2) {
    int &ans = d[t][s1][s2];
    if (t == n + m) return s2 == (1<<s)-1 ? 0 : INF;
    if (ans != -1) return ans;
    ans = INF;
    if (t >= m) ans = dp(t+1, s0, s1, s2);
    int m0 = st[t] & s0, m1 = st[t] & s1;
    s0 ^= m0; s1 = (s1 ^ m1) | m0; s2 |= m1;
    ans = min(ans, c[t] + dp(t+1, s0, s1, s2));
    return ans;
}

int main() {
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        ss >> s >> m >> n;
        if (s == 0) break;
        memset(st, 0, sizeof(st));
        for (int i = 0; i < m + n; i++) {
            getline(cin, line);
            stringstream ss(line);
            ss >> c[i]; int x;
            while (ss >> x) st[i] |= 1<<(x-1);
        }
        memset(d, -1, sizeof(d));
        cout << dp(0, (1<<s)-1, 0, 0) << endl;
    }
    return 0;
}
