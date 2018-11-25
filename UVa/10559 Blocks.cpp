#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define maxn 205

int n;
int A[maxn];
int d[maxn][maxn][maxn];

int dp(int i, int j, int k) {
    if (i > j) return 0;
    int &ans = d[i][j][k];
    if (ans >= 0) return ans;
    int p = j;
    while (p >= i && A[p] == A[j]) p--; p++;
    ans = dp(i, p-1, 0) + (k+j-p+1)*(k+j-p+1);
    for (int q = i; q < p; q++)
        if (A[q] == A[j] && A[q] != A[q+1])
            ans = max(ans, dp(q+1, p-1, 0) + dp(i, q, k+j-p+1));
    return ans;
}

int main() {
    int T; scanf("%d", &T);
    int kase = 0;
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d", &A[i]);
        memset(d, -1, sizeof(d));
        printf("Case %d: %d\n", ++kase, dp(0, n-1, 0));
    }
    return 0;
}
