#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 1000+10
using namespace std;

int dp[maxn], p[maxn][maxn], vis[maxn][maxn];
char str[maxn];
int n, kase;

bool is_palindrome(int i, int j) {
    if (i >= j) return true;
    if (str[i] != str[j]) return false;
    if (vis[i][j] == kase) return p[i][j];
    vis[i][j] = kase;
    p[i][j] = is_palindrome(i+1, j-1);
    return p[i][j];
}

int main() {
    int T; scanf("%d", &T);
    for (kase = 1; kase <= T; kase++) {
        scanf("%s", str+1);
        n = (int)strlen(str+1);
        for (int i = 1; i <= n; i++) {
            dp[i] = i;
            for (int j = 0; j <= i-1; j++)
                if (is_palindrome(j+1, i)) dp[i] = min(dp[i], dp[j]+1);
        }
        printf("%d\n", dp[n]);
    }
    return 0;
}
