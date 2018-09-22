#include <bits/stdc++.h>

using namespace std;

long long n, k, mod;

struct Matrix {
  long long mat[2][2];
  int r, c;
  void init(const int &r, const int &c) {
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        mat[i][j] = 0;
      }
    }
    this->r = r;
    this->c = c;
  }
  void set(int r, int c, long long v) {
    mat[r][c] = v;
  }
};

long long mul(long long a, long long b) {
  long long ret = 0;
  while (b) {
    if (b & 1) {
      (ret += a) %= mod;
    }
    b >>= 1;
    (a *= 2) %= mod;
  }
  return ret;
}

Matrix mul(Matrix &A, Matrix &B) {
  assert(A.c == B.r);
  Matrix ret;
  ret.init(A.r, B.c);
  for (int i = 0; i < A.r; i++) {
    for (int j = 0; j < B.c; j++) {
      for (int k = 0; k < A.c; k++) {
        (ret.mat[i][j] += mul(A.mat[i][k], B.mat[k][j])) %= mod;
      }
    }
  }
  return ret;
}

int main() {
  scanf("%lld %lld %lld", &n, &k, &mod);
  k %= mod;
  if (n == 1) {
    printf("%lld\n", (k - 1 + mod) % mod);
    return 0;
  }
  if (n == 2) {
    printf("%lld\n", mul(k, k - 1));
    return 0;
  }
  Matrix unit;
  unit.init(2, 2);
  unit.set(0, 0, k-1);
  unit.set(0, 1, 1);
  unit.set(1, 0, k-1);
  unit.set(1, 1, 0);
  n -= 2;
  Matrix p;
  p.init(2, 2);
  p.set(0, 0, 1);
  p.set(1, 1, 1);
  while (n) {
    if (n & 1LL) {
      p = mul(p, unit);
    }
    n = n / 2;
    if (n) {
      unit = mul(unit, unit);
    }
  }
  Matrix ans;
  ans.init(1, 2);
  ans.set(0, 0, mul(k-1, k-1));
  ans.set(0, 1, k-1);
  ans = mul(ans, p);
  printf("%lld\n", (ans.mat[0][0] + ans.mat[0][1]) % mod);
  return 0;
}
