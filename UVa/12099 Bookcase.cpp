#include <cstdio>
#include <algorithm>
#define maxn 75
#define maxt maxn*30
#define INF 1000000000
#define FOR(i, x, y) for (int i = x; i <= y; i++)
using namespace std;

struct Book {
    int h, t;
    bool operator < (const Book &rhs) const {
        return h > rhs.h || (h == rhs.h && t > rhs.t);
    }
} books[maxn];

int n;
int sum[maxn];
int dp[2][maxt][maxt];

void update(int &x, int v) {
    if (x > v || x == -1) x = v;
}

int f(int t, int h) {
    return t == 0 ? h : 0;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        FOR(i, 1, n)
            scanf("%d%d", &books[i].h, &books[i].t);
        sort(books+1, books+1+n);
        
//        sum[0] = 0;
        FOR(i, 1, n) sum[i] = sum[i-1] + books[i].t;
        
        int t = 0;
        dp[0][0][0] = 0;
        
        FOR(i, 1, n) {
            FOR(j, 0, sum[i]) FOR(k, 0, sum[i]-j)
            dp[t^1][j][k] = -1;
            
            FOR(j, 0, sum[i-1]) FOR(k, 0, sum[i-1]-j) if(~dp[t][j][k]) {
                update(dp[t^1][j][k], dp[t][j][k]); // layer 1
                update(dp[t^1][j+books[i].t][k], dp[t][j][k] + f(j, books[i].h)); // layer 2
                update(dp[t^1][j][k+books[i].t], dp[t][j][k] + f(k, books[i].h)); // layer 3
            }
            
            t ^= 1;
        }
        
        int ans = INF;
        FOR(i, 1, sum[n]) FOR(j, 1, sum[n]-i) if (~dp[t][i][j]) {
            int h = books[1].h + dp[t][i][j];
            int t = max(max(i, j), sum[n]-i-j);
            ans = min(ans, h*t);
        }
        
        printf("%d\n", ans);
    }
    return 0;
}
