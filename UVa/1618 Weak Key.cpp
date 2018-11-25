#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 10000;
int n;
int A[maxn], B[maxn];
int max_B[maxn][100], min_A[maxn][100], max_A[maxn][100];

void ST() {
    memset(max_B, 0, sizeof(max_B));
    memset(max_A, 0, sizeof(max_A));
    memset(min_A, 0, sizeof(min_A));
    for (int i = 0; i < n; i++) { max_B[i][0] = B[i]; min_A[i][0] = max_A[i][0] = A[i]; }
    for (int p = 1; (1<<p) < n; p++)
        for (int i = 0; i < n; i++) {
            max_B[i][p] = max(max_B[i][p-1], max_B[i+(1<<(p-1))][p-1]);
            min_A[i][p] = min(min_A[i][p-1], min_A[i+(1<<(p-1))][p-1]);
            max_A[i][p] = max(max_A[i][p-1], max_A[i+(1<<(p-1))][p-1]);
        }
}

int RMQ_B(int l, int r) {
    int p = log2(r-l+1);
    return max(max_B[l][p], max_B[r-(1<<p)+1][p]);
}

int RMQ_A(int l, int r, int type) {
    int p = log2(r-l+1);
    return (type == 1 ? max(max_A[l][p], max_A[r-(1<<p)+1][p]) : min(min_A[l][p], min_A[r-(1<<p)+1][p]));
}

void debug() {
    for (int i = 0; i < n; i++)
        for (int j = 0; (1<<j) < 2 * n; j++)
            printf("max[%d][%d] = %d\n", i, j, max_B[i][j]);
    for (int i = 0; i < n; i++)
        for (int j = 0; (1<<j) < 2 * n; j++)
            printf("min[%d][%d] = %d\n", i, j, min_A[i][j]);
}

bool cmp(int x, int y) {
    return A[x] > A[y];
}

int main() {
    /// freopen("test.in", "r", stdin);
    /// freopen("read.in", "r", stdin);
    
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d", &A[i]);
        
        for(int i = 0; i < n; i++) B[i] = i;
        sort(B, B+n, cmp);
        /// for(int i = 0; i < n; i++) printf("%d ", A[B[i]]); printf("\n");
        
        ST(); bool ok = false;
        int pos_p, pos_q, pos_s, Ar;
        for (int i = 0; i < n; i++)
            for (int j = i + 2; j < n; j++) {
                if (ok) break;
                pos_p = B[j], pos_q = B[i]; /// decreasing
                pos_s = RMQ_B(i+1, j-1);
                if (pos_p < pos_q && pos_q +1 < pos_s) {
                    Ar = RMQ_A(pos_q+1, pos_s-1, 0);
                    if (Ar < A[pos_p]) { puts("YES"); ok = true; break; }
                }
                swap(pos_p, pos_q); /// increasing
                if (pos_p < pos_q && pos_q +1 < pos_s) { /// keep position s
                    Ar = RMQ_A(pos_q+1, pos_s-1, 1);
                    if (Ar > A[pos_p]) { puts("YES"); ok = true; break; }
                }
            }
        if (!ok) puts("NO");
    }
    return 0;
}

