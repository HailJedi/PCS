#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

const int K = 100;
const int N = 100 * 1000 + 13;
const long long INF64 = 3e18;

int mu[K];

void precalc(){
    static bool prime[K];
    static int lst[K];

    memset(prime, false, sizeof(prime));
    forn(i, K) lst[i] = i;

    for (int i = 2; i < K; ++i){
        if (lst[i] == i) mu[i] = 1;
        for (int j = 2 * i; j < K; j += i){
            lst[j] = min(lst[j], lst[i]);
            if (lst[j] == lst[i])
                mu[j] = 0;
            else
                mu[j] = -mu[i];
        }
    }
}

int mx[K];

long long binpow(long long a, int b){
    long long res = 1;
    while (b){
        if (b & 1){
            if (res < INF64 / a) res *= a;
            else return INF64;
        }
        if (b > 1){
            if (a < INF64 / a) a *= a;
            else return INF64;
        }
        b >>= 1;
    }
    return res;
}

long long calc(long long n){
    int pw = 63 - __builtin_clzll(n);
    for (int i = 3; i <= pw; ++i){
        if (mu[i] == 0) continue;
        while (binpow(mx[i], i) > n)
            --mx[i];
    }

    long long res = n - 1;
    for (int i = 2; i <= pw; ++i)
        res -= mu[i] * (mx[i] - 1);

    return res;
}

int get_sqrt(long long n){
    int l = 1, r = 1000000000;
    while (l < r - 1){
        int m = (l + r) / 2;
        if (m * 1ll * m <= n)
            l = m;
        else
            r = m;
    }
    return (r * 1ll * r <= n ? r : l);
}

long long ans[N];

int main() {
    freopen("read.in", "r", stdin);
    freopen("std.out", "w", stdout);
    precalc();
    int T;
    scanf("%d", &T);
    vector<pair<long long, int>> q;

    forn(i, T){
        long long n;
        scanf("%lld", &n);
        q.push_back({n, i});
    }

    sort(q.begin(), q.end(), greater<pair<long long, int>>());
    mx[3] = 1000000;
    mx[4] = 31622;
    mx[5] = 3981;
    for (int i = 6; i < K; ++i)
        mx[i] = 1000;

    forn(z, T){
        long long n = q[z].first;
        mx[2] = get_sqrt(n);
        ans[q[z].second] = calc(n);
    }

    forn(i, T)
        printf("%lld\n", ans[i]);
    return 0;
}
