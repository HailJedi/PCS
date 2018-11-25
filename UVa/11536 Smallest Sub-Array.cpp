#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int A[1000001], Q[1000001], cnt[1001];
int N, M, K;

int main()
{
    freopen("read.in", "r", stdin);
    
    int T; scanf("%d", &T);
    for (int kase = 1; kase <= T; kase++) {
        printf("Case %d: ", kase);
        scanf("%d%d%d", &N, &M, &K);
        
        A[1] = 1, A[2] = 2, A[3] = 3;
        for (int i = 4; i <= N; i++)
            A[i] = (A[i-3] + A[i-2] + A[i-1]) % M +1;
        
        int head = 1, tail = 1; Q[head] = A[head];
        memset(cnt, 0, sizeof(cnt));
        int ans = 0x3f3f3f3f;
        while (head < N) {
            while (head < N && cnt[A[head]] == 0) { Q[++head] = A[head]; cnt[A[head]]++; }
            ans = min(ans, head - tail);
            while (cnt[Q[tail]] >= 2 && tail <= N) { cnt[Q[tail++]]--; }
            cnt[Q[tail++]]--;
        }
        printf("%d\n", ans);
    }
    return 0;
}

