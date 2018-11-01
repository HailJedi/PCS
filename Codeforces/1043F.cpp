/*
Created 2018-11-01
"Make It One"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 300000 + 5;
const int P = 10;
const int mod = 19260817;

int f[P][N];
int fac[N], inv[N];
int cnt[N];

int power(int a, int n) {
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

void sub(int &x, int y) {
  x -= y;
  while (x < 0) {
    x += mod;
  }
}

int C(int n, int k) {
  if (k > n) {
    return 0;
  }
  return 1LL * fac[n] * inv[k] % mod * inv[n-k] % mod;
}

int main() {
  int n;
  scanf("%d", &n);
  fac[0] = 1;
  for (int i = 1; i < N; i++) {
    fac[i] = 1LL * fac[i-1] * i % mod;
  }
  inv[N-1] = power(fac[N-1], mod-2);
  for (int i = N-1; i >= 1; i--) {
    inv[i-1] = 1LL * inv[i] * i % mod;
  }
  for (int i = 1; i <= n; i++) {
    int a;
    scanf("%d", &a);
    cnt[a]++;
  }
  for (int i = 1; i < N; i++) {
    for (int j = i*2; j < N; j += i) {
      cnt[i] += cnt[j];
    }
  }
  for (int i = 1; i < P; i++) {
    for (int j = N-1; j >= 1; j--) {
      f[i][j] = C(cnt[j], i);
      for (int k = j*2; k < N; k += j) {
        sub(f[i][j], f[i][k]);
      }
    }
    if (f[i][1] > 0) {
      printf("%d\n", i);
      return 0;
    }
  }
  printf("-1\n");
  return 0;
}
