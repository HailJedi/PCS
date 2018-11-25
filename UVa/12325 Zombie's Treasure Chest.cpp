#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long long N;
long long S[2], V[2];
long long cnt[2];

long long solve_1(int item, long long up_bound) {
    long long value = -10000;
    for (cnt[item] = up_bound; cnt[item] >= 0; cnt[item]--) {
        cnt[item^1] = (N - cnt[item] * S[item]) / S[item^1];
        value = max(value, cnt[item] * V[item] + cnt[item^1] * V[item^1]);
    }
    return value;
}

long long solve() {
    if (S[0] * S[1] < N) {
        if (S[0]*V[1] < S[1]*V[0]) {
            return solve_1(1, S[0]-1);
        } else {
            return solve_1(0, S[1]-1);
        }
    } else {
        if (S[0] < S[1]) {
            return solve_1(1, N/S[1]);
        } else {
            return solve_1(0, N/S[0]);
        }
    }
}

int main() {
    // insert code here...
    int T; scanf("%d", &T);
    int kase = 0;
    while (T--) {
        scanf("%lld%lld%lld%lld%lld", &N, &S[0], &V[0], &S[1], &V[1]);
        printf("Case #%d: %lld\n", ++kase, solve());
    }
    return 0;
}
