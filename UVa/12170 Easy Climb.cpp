#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;

#define maxn 105
#define maxx maxn*maxn*2
#define INF (1LL << 60)

LL h[maxn], x[maxx], dp[2][maxx];
int n;
LL d;

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> d;
        for (int i = 1; i <= n; i++) cin >> h[i];
        if (abs(h[1] - h[n]) > (n-1)*d) {
            cout << "impossible\n";
            continue;
        }
        
        int nx = 0;
        for (int i = 1; i <= n; i++)
            for (int j = -n+1; j <= n-1; j++)
                x[++nx] = h[i] + j * d;
        sort(x+1, x+nx+1);
        nx = int(unique(x+1, x+1+nx) - (x+1));
        
        int t = 0;
        for (int i = 1; i <= nx; i++) {
            dp[t][i] = INF;
            if (x[i] == h[1]) dp[t][i] = 0;
        }
        for (int i = 2; i <= n; i++) {
            int k = 1;
            for (int j = 1; j <= nx; j++) {
                while (k < nx && x[k] < x[j]-d) k++;
                while (k+1 <= nx && x[k+1] <= x[j]+d && dp[t][k+1] <= dp[t][k]) k++;
                if (dp[t][k] == INF) dp[t^1][j] = INF;
                else dp[t^1][j] = dp[t][k] + abs(x[j] - h[i]);
            }
            t ^= 1;
        }
        for (int i = 1; i <= nx; i++)
            if (x[i] == h[n]) cout << dp[t][i] << endl;
    }
    return 0;
}
