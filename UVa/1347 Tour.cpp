#include <cstdio>
#include <algorithm>
#include <cmath>
#define maxn 100
using namespace std;

pair<double, double> p[maxn];
int n;
double dp[maxn][maxn];

double dist(int a, int b) {
    return sqrt(pow(p[a].first-p[b].first, 2) + pow(p[a].second-p[b].second, 2));
}

int main() {
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; i++)
            scanf("%lf%lf", &p[i].first, &p[i].second);
        sort(p+1, p+n+1);
        
        for (int i = 1; i <= n-2; i++)
            dp[n-1][i] = dist(n, n-1) + dist(i, n);
        
        for (int i = n-2; i >= 1; i--)
            for (int j = i-1; j >= 1; j--)
                dp[i][j] = min(dp[i+1][j]+dist(i+1, i), dp[i+1][i] + dist(j, i+1));
        
        printf("%.2lf\n", dp[2][1] + dist(2, 1));
    }
}
