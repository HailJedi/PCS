#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

#define maxn 16
#define FOR(i, x, y) for(int i = x; i < y; i++)

struct Tips {
    string forw, back;
    bool operator < (const Tips &rhs) const {
        return forw.length() < rhs.forw.length();
    }
} tips[maxn];

int n;
string s[maxn][2];
int over_lenth[maxn][2][maxn][2];
int d[1<<maxn][maxn][2];
int lenth[maxn];

int calc_lenth(int i, int a, int j, int b) {
    string str1 = s[i][a], str2 = s[j][b]; // put str2 rigth side of str1
    int len1 = (int)str1.length(), len2 = (int)str2.length();
    FOR(i, 1, len1) {
        if (i + len2 <= len1) continue;
        bool ok = true;
        FOR(j, 0, len1-i)
            if (str1[j+i] != str2[j]) { ok = false; break; }
        if (ok) return len1 - i;
    }
    return 0;
}

void init() {
//    read in
    FOR(i, 0, n) {
        cin >> tips[i].forw;
        tips[i].back = tips[i].forw;
        reverse(tips[i].back.begin(), tips[i].back.end());
    }
    sort(tips, tips+n);
    
//    delete overlapped strings
    int n2 = 0;
    FOR(i, 0, n) {
        bool keep = true;
        FOR(j, i+1, n) {
            string str1 = tips[i].forw, str2 = tips[j].forw, str3 = tips[j].back;
            if (str2.find(str1) != string::npos || str3.find(str1) != string::npos)
                { keep = false; break; }
        }
        if (keep) {
            s[n2][0] = tips[i].forw;
            s[n2][1] = tips[i].back;
            lenth[n2] = (int)tips[i].forw.length();
            n2++;
        }
    }
    n = n2;
    
//    calculate overlapping length
    FOR(i, 0, n) FOR(a, 0, 2)
        FOR(j, 0, n) FOR(b, 0, 2)// if (i != j)
            over_lenth[i][a][j][b] = calc_lenth(i, a, j, b);
}

void update(int &x, int nv) {
    if (x == -1 || x > nv) x = nv;
}

void solve() {
//    calculate dp
    memset(d, -1, sizeof(d));
    d[1][0][0] = lenth[0];
    int all = (1<<n)-1;
    FOR(s, 1, all)
        FOR(i, 0, n) FOR(t, 0, 2) if (~d[s][i][t])
            FOR(j, 1, n) FOR(q, 0, 2) if (!(s&(1<<j)))
                update(d[s|(1<<j)][j][q], d[s][i][t] + lenth[j] - over_lenth[i][t][j][q]);
    
//    find answer
    int ans = -1;
    FOR(i, 0, n) FOR(s, 0, 2)
        if (~d[all][i][s])
            update(ans, d[all][i][s] - over_lenth[i][s][0][0]);
    
    if (ans <= 1) ans = 2;
    cout << ans << endl;
}


int main() {
    ios::sync_with_stdio(false);
    while (cin >> n && n) {
        init();
        solve();
    }
    return 0;
}
