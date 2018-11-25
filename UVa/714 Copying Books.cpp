#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxm = 500 + 5;
int m, k, p[maxn];

int solve(long long maxp) {
    
}

int last[maxm];
void print(long long ans) {
    
}

int main() {
    freopen("input.in", "r", stdin);
    
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        long long tot = 0;
        int maxp = -1;
        for (int i = 0; i < n; i++) {
            scanf("%d", &p[i]);
            tot += p[i];
            maxp = max(maxp, p[i]);
        }
        long long L = maxp, R = tot;
        while (L < R) {
            long long M = (L + R) / 2;
            if (solve(M) <= k) R = M;
            else L = M + 1;
        }
        print(L);
    }
    return 0;
}

