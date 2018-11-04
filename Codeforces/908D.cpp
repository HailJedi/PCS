/*
Created 2018-11-04
"New Year and Arbitrary Arrangement"
*/

#include <bits/stdc++.h>

using namespace std;

const int K = 1000 + 5;
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

int f[K][K];
int k, pa, pb, Pa, Pb, inv_pb;

int solve(int ab, int a) {
  if (ab + a >= k) {
    return ((ab + a) % mod + 1LL * pa * inv_pb % mod) % mod;
  }
  if (f[ab][a] != 0) {
    return f[ab][a];
  }
  return f[ab][a] = (1LL * Pa * solve(ab, a+1) % mod + 1LL * Pb * solve(ab+a, a) % mod) % mod;
}

int main() {
  scanf("%d %d %d", &k, &pa, &pb);
  Pa = 1LL * pa * power(pa+pb, mod-2) % mod;
  Pb = 1LL * pb * power(pa+pb, mod-2) % mod;
  inv_pb = power(pb, mod-2);
  printf("%d\n", solve(0, 1));
  return 0;
}
