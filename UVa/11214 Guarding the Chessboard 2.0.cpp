#include <iostream>
#include <cstring>
using namespace std;

const int buf = 10;
int grid[50][50];
int quen[4][50];
int r, c;
int kase;
int maxd;

bool judge() {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if (grid[i][j] && !quen[0][i] && !quen[1][j] && !quen[2][i+j] && !quen[3][buf+i-j])
                return false;
    return true;
}

bool dfs(int k, int cur) {
    if (k == maxd) {
        return judge();
    }
    
    for (int sel = cur; sel < r * c; sel++) {
        int nr = sel / c, nc = sel % c;
        int t0 = quen[0][nr], t1 = quen[1][nc], t2 = quen[2][nr+nc], t3 = quen[3][buf+nr-nc];
        quen[0][nr] = quen[1][nc] = quen[2][nr+nc] = quen[3][buf+nr-nc] = 1;
        if (dfs(k+1, sel)) return true;
        quen[0][nr] = t0; quen[1][nc] = t1; quen[2][nr+nc] = t2; quen[3][buf+nr-nc] = t3;
    }
    
    return false;
}

void solve() {
    for (maxd = 0; ; maxd++) {
        memset(quen, 0, sizeof(quen));
        if (dfs(0, 0)) break;
    }
    cout << "Case " << ++kase << ": " << maxd << endl;
}

int main() {
    while (cin >> r >> c && r && c) {
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++) {
                char t; cin >> t;
                grid[i][j] = (t == 'X' ? 1 : 0);
            }
        solve();
    }
    return 0;
}
