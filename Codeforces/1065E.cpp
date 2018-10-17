/*
Created 2018-10-17
"Side Transmutations"
A counting problem
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 200000 + 5;
const int mod = 998244353;

int n, m, A;
int b[N];

int mul(int a, int b) {
  return 1LL * a * b % mod;
}

int add(int a, int b) {
  return (a + b) % mod;
}

int power(int a, int n) {
  int b = 1;
  for (; n; n >>= 1, a = mul(a, a)) {
    if (n & 1) {
      b = mul(b, a);
    }
  }
  return b;
}

int solve(int len) {
  int base = power(A, len);
  return mul(add(mul(base, base), base), power(2, mod-2));
}

int main() {
  scanf("%d %d %d", &n, &m, &A);
  A %= mod;
  for (int i = 1; i <= m; i++) {
    scanf("%d", &b[i]);
  }
  int ans = power(A, n-b[m]*2);
  ans = mul(ans, solve(b[1]));
  for (int i = 2; i <= m; i++) {
    ans = mul(ans, solve(b[i]-b[i-1]));
  }
  printf("%d\n", ans);
  return 0;
}
