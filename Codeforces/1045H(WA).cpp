/*
Creatd 2018-10-09
"Self-exploration"
A counting problem
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const int mod = 1e9 + 7;

char in[N];
int A[N], B[N];
int na, nb;
int c[2][2];
int digit_count;
int fac[N];

int POW(int a, int n) {
  int b = 1;
  while (n) {
    if (n & 1) {
      b = 1LL * b * a % mod;
    }
    a = 1LL * a * a % mod;
    n >>= 1;
  }
  return b;
}

int C(int n, int k) {
  if (k == 0) {
    return 1;
  }
  return 1LL * fac[n] * POW(fac[k], mod-2) % mod * POW(fac[n-k], mod-2) % mod;
}

int solve(int h, int c[2][2]) {
  if (c[h][h^1] - c[h^1][h] > 1 || c[h][h^1] - c[h^1][h] < 0) {
    return 0;
  }
  if (c[0][0] < 0 || c[0][1] < 0 || c[1][0] < 0 || c[1][1] < 0) {
    return 0;
  }
  int one = c[h^1][h] + 1;
  int zero = c[h][h^1];
  return 1LL * C(zero + c[h^1][h^1] - 1, c[h^1][h^1]) * C(one + c[h][h] - 1, c[h][h]) % mod;
}

int f(int *a, int n) {
  if (n < digit_count) {
    return 0;
  }
  int c2[2][2];
  memcpy(c2, c, sizeof c);
  int ret = 0;
  if (n > digit_count) {
    ret = solve(1, c);
    for (int i = 2; i <= n; i++) {
      c2[a[i-1]][a[i]]--;
    }
  } else {
    for (int i = 2; i <= n; i++) {
      if (a[i] == 1) {
        c2[a[i-1]][0]--;
        if (i != n) {
          c2[0][0]--;
          (ret += solve(0, c2)) %= mod;
          c2[0][0]++;
          c2[0][1]--;
          (ret += solve(1, c2)) %= mod;
          c2[0][1]++;
        } else {
          ret += (*max_element(c2, c2+4) == 0 && *min_element(c2, c2+4) == 0);
        }
        c2[a[i-1]][0]++;
      }
      c2[a[i-1]][a[i]]--;
    }
  }
  return ret + (*max_element(c2, c2+4) == 0 && *min_element(c2, c2+4) == 0);
}

int main() {
  // freopen("read.in", "r", stdin);
  scanf("%s", in+1);
  na = strlen(in+1);
  for (int i = 1; i <= na; i++) {
    A[i] = in[i] - '0';
  }
  scanf("%s", in+1);
  nb = strlen(in+1);
  for (int i = 1; i <= nb; i++) {
    B[i] = in[i] - '0';
  }
  scanf("%d %d %d %d", &c[0][0], &c[0][1], &c[1][0], &c[1][1]);
  digit_count = c[0][0] + c[0][1] + c[1][0] + c[1][1] + 1;
  fac[0] = 1;
  for (int i = 1; i < N; i++) {
    fac[i] = 1LL * fac[i-1] * i % mod;
  }
  int ans = f(B, nb) - f(A, na);
  for (int i = 2; i <= na; i++) {
    c[A[i-1]][A[i]]--;
  }
  ans += (*max_element(c, c+4) == 0 && *min_element(c, c+4) == 0);
  printf("%d\n", (ans % mod + mod) % mod);
  return 0;
}
