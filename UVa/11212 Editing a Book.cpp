#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 10;
int maxd;
int A[maxn];
int n;

void input() {
    memset(A, 0, sizeof(A));
    for (int i = 1; i <= n; i++) cin >> A[i];
}

int h() {
    int h = 0;
    for (int i = 1; i < n; i++)
        if(A[i]+1 != A[i+1]) h++;
    if(A[n] != n) h++;
    return h;
}

bool dfs(int dist) {
    if (h() == 0) return true;
    if (3 * dist + h() > 3 * maxd) return false;

    int oldA[maxn];
    memcpy(oldA, A, sizeof(A));
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            
            int B[maxn];
            int cnt = 1;
            for (int k = 1; k <= n; k++) {
                if (k < i || k > j) B[cnt++] = A[k];
            }
            
            for (int k = 1; k <= cnt; k++) if(k != i) {
                int cnt2 = 1;
                for (int l = 1; l < k; l++) A[cnt2++] = B[l];
                for (int l = i; l <= j; l++) A[cnt2++] = oldA[l];
                for (int l = k; l < cnt; l++) A[cnt2++] = B[l];
                
                if(dfs(dist+1)) return true;
                memcpy(A, oldA, sizeof(oldA));
            }
        }
    }
    return false;
}

int solve() {
    int max_ans = 5;
    for (maxd = 0; maxd < max_ans; maxd++) {
        //cout << "maxd: " << maxd << endl;
        if(dfs(0)) return maxd;
    }
    return max_ans;
}

int main() {
    // insert code here...
    ios::sync_with_stdio(false);
    int kase = 0;
    while (cin >> n && n) {
        input();
        cout << "Case " << ++kase << ": " << solve() << endl;
    }
    return 0;
}
