#include <cstdio>
#include <stack>
using namespace std;

const int maxn = 100010;
long long A[maxn], L[maxn], R[maxn], S[maxn];
int n;
stack<int> stk;

void init() {
    A[0] = A[n+1] = -0x3f3f3f3f;
    while (!stk.empty()) stk.pop();
    stk.push(0);
    for (int i = 1; i <= n; i++) {
        while (A[stk.top()] >= A[i]) stk.pop();
        L[i] = stk.top();
        stk.push(i);
    }
    while (!stk.empty()) stk.pop();
    stk.push(n+1);
    for (int i = n; i >= 1; i--) {
        while (A[stk.top()] >= A[i]) stk.pop();
        R[i] = stk.top();
        stk.push(i);
    }
}

int main() {
//    freopen("write.txt", "w", stdout);
    bool first = true;
    while (scanf("%d", &n) == 1) {
        if (first) first = false;
        else puts("");
        
        S[0] = 0;
        for (int i = 1; i <= n; i++) { scanf("%lld", &A[i]); S[i] = S[i-1] + A[i]; }
        
        init();
        
        long long ans = -0x3f3f3f3f;
        long long xl = 1, xr = 1;
        for (int i = 1; i <= n; i++) {
            long long s = S[R[i]-1] - S[L[i]];
            if (s * A[i] > ans || (s * A[i] == ans && xr - xl > R[i] - L[i] - 1)) {
                ans = s * A[i];
                xl = L[i]+1; xr = R[i]-1;
            }
        }
        if (ans == 0) puts("0\n1 1");
        else printf("%lld\n%lld %lld\n", ans, xl, xr);
    }
    
    return 0;
}
