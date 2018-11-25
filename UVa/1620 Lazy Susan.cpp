#include <cstdio>
using namespace std;

int A[501];
int n;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &A[i]);
        int cnt = 0;
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                if (A[i] > A[j]) cnt++;
        if (!(cnt&1) || !(n&1)) puts("possible");
        else puts("impossible");
    }
}
