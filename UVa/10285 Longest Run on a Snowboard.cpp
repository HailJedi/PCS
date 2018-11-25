#include <iostream>
#include <string>
using namespace std;

const int INF = 1e10;
const int maxn = 100+5;
string name;
int R, C, kase;
int h[maxn][maxn];
int d[maxn][maxn];
int vis[maxn][maxn];
const int dr[] = {0, 1, -1, 0, 0};
const int dc[] = {0, 0, 0, 1, -1};

int dp(int r, int c) {
    if (r == 0 || r == R+1 || c == 0 || c == C+1) return -INF;
    int &ans = d[r][c];
    if (vis[r][c] == kase) return ans;
    vis[r][c] = kase;
    ans = 1;
    for (int i = 1; i <= 4; i++) {
        int nr = r + dr[i], nc = c + dc[i];
        if (h[nr][nc] < h[r][c])
            ans = max(ans, 1+dp(nr, nc));
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    for (kase = 1; kase <= T; kase++) {
        cin >> name >> R >> C;
        for (int i = 1; i <= R; i++)
            for (int j = 1; j <= C; j++)
                cin >> h[i][j];
        int ans = 0;
        for (int r = 1; r <= R; r++)
            for (int c = 1; c <= C; c++)
                ans = max(ans, dp(r, c));
        cout << name << ": " << ans << endl;
    }
    return 0;
}
