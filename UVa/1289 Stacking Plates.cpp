#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int INF = 1e9;
const int maxm = 2500;
const int maxn = 50;

int dp[maxm][maxn];
int exist[maxm][maxn];
int amount[maxm];

int main() {
    int kase = 0;
    int N, H, x;

    while (scanf("%d", &N) == 1) {
        vector< pair<int, int> > plates;
        for (int i = 0; i < N; i++) {
            scanf("%d", &H);
            for (int j = 0; j < H; j++) {
                scanf("%d", &x);
                plates.push_back(make_pair(x, i));
            }
        }
        sort(plates.begin(), plates.end());
        plates.resize(unique(plates.begin(), plates.end()) - plates.begin());

        memset(exist, 0, sizeof(exist));

        int M = 0;
        for (int i = 0; i < plates.size(); ) {
            int j = i, cnt = 0;
            while (j < plates.size() && plates[i].first == plates[j].first) {
                cnt++; exist[M][plates[j].second] = 1; j++;
            }
            amount[M] = cnt; i = j; M++;
        }

        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++) dp[i][j] = INF;

        for (int i = 0; i < N; i++)
            if (exist[0][i]) dp[0][i] = amount[0];

        for (int i = 1; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (exist[i][j]) {
                    for (int k = 0; k < N; k++) {
                        if (exist[i][k] && (j != k || amount[i] == 1))
                            dp[i][j] = min(dp[i][j], dp[i-1][k] + amount[i] - 1);
                        else 
                            dp[i][j] = min(dp[i][j], dp[i-1][k] + amount[i]);
                    }
                }

            }
        }

        int ans = INF;
        for (int i = 0; i < N; i++)
            ans = min(ans, dp[M-1][i]);
        printf("Case %d: %d\n", ++kase, ans * 2 - N - 1);
    }
    return 0;
}