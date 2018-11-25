#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 25;
int n;
int p[5];
int w[maxn];
int wi;
int ans;

bool judge(int p0, int p1, int p2, int p3, int p4) {
    return !((p0&p[0]) || (p1&p[1]) || (p2&p[2]) || (p3&p[3]) || (p4&p[4]));
}

void init() {
    string str;
    memset(p, 0, sizeof(p));
    for (int unit = 0; unit < 5; unit++) {
        cin >> str;
        for (int i = n-1; i >= 0; i--)
            if (str[i] == 'X') p[unit] |= (1<<i);
    }
    wi = 0; ans = 10 * n;
    for (int lp = 1; lp <= n; lp++)
        if (judge((p[0]>>lp), (p[1]>>lp), (p[2]>>lp), (p[3]>>lp), (p[4]>>lp)))
            w[wi++] = lp;
}

void dfs(int s0, int s1, int s2, int s3, int s4, int d, int len) {
    if (len + w[0]*(10-d) > ans) return;
    if (d == 10) {
        ans = min(ans, len);
        return;
    }
    for (int i = 0; i < wi; i++) {
        int lp = w[i];
        int ss0 = (s0>>lp), ss1 = (s1>>lp), ss2 = (s2>>lp), ss3 = (s3>>lp), ss4 = (s4>>lp);
        if(judge(ss0, ss1, ss2, ss3, ss4)) {
            dfs(ss0^p[0], ss1^p[1], ss2^p[2], ss3^p[3], ss4^p[4], d+1, len+w[i]);
        }
    }
}

int main() {
    while (cin >> n && n) {
        init();
        dfs(p[0], p[1], p[2], p[3], p[4], 1, n);
        cout << ans << endl;
    }
    return 0;
}
