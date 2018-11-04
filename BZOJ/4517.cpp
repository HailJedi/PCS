/*
Created 2018-11-04
"[Sdoi2016]排列计数"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;
const int mod = 1e9 + 7;

int power(int a, int n) {
  int b = 1;
  for (; n; n >>= 1, a = 1LL * a * a % mod) {
    if (n & 1) {
      b = 1LL * b * a % mod;
    }
  }
  return b;
}

int fac[N], inv[N];
int cnt[N];

int C(int n, int k) {
  return 1LL * fac[n] * inv[k] % mod * inv[n-k] % mod;
}

int main() {
  fac[0] = 1;
  for (int i = 1; i < N; i++) {
    fac[i] = 1LL * fac[i-1] * i % mod;
  }
  inv[N-1] = power(fac[N-1], mod-2);
  for (int i = N-1; i > 0; i--) {
    inv[i-1] = 1LL * inv[i] * i % mod;
  }
  assert(inv[1] == 1);
  cnt[0] = 1;
  cnt[1] = 0;
  for (int i = 2; i < N; i++) {
    cnt[i] = 1LL * (i-1) * (cnt[i-1] + cnt[i-2]) % mod;
  }
  int T, n, m;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    printf("%lld\n", 1LL * C(n, m) * cnt[n-m] % mod);
  }
  return 0;
}
