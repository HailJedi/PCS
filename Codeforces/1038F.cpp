/*
Created 2018-10-11
"Wrap Around"
A matrix solution
*/

#include <bits/stdc++.h>

using namespace std;

const int M = 100 + 5;

int n, m;
char str[M];
int pre[M];

struct Matrix {
  long long a[M][M];
  Matrix(long long v = 0) {
    memset(a, 0, sizeof a);
    for (int i = 0; i < m; i++) {
      a[i][i] = v;
    }
  }
  long long *operator[](const int idx) {
    return a[idx];
  }
  Matrix operator * (Matrix &B) const {
    Matrix ret;
    for (int k = 0; k < m; k++) {
      for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
          ret[i][j] += a[i][k] * B[k][j];
        }
      }
    }
    return ret;
  }
};

int main() {
  // freopen("read.in", "r", stdin);
  scanf("%d %s", &n, str+1);
  m = strlen(str+1);
  int k = 0;
  for (int i = 2; i <= m; i++) {
    while (k && str[k+1] != str[i]) {
      k = pre[k];
    }
    k += str[k+1] == str[i];
    pre[i] = k;
  }
  Matrix A = Matrix();
  for (int i = 0; i < m; i++) {
    k = i;
    while (k && str[k+1] != '0') {
      k = pre[k];
    }
    k += str[k+1] == '0';
    A[i][k]++;
    k = i;
    while (k && str[k+1] != '1') {
      k = pre[k];
    }
    k += str[k+1] == '1';
    A[i][k]++;
  }
  long long cnt = 1LL << n;
  Matrix ans(1);
  while (n) {
    if (n & 1) {
      ans = ans * A;
    }
    A = A * A;
    n >>= 1;
  }
  for (int i = 0; i < m; i++) {
    cnt -= ans[i][i];
  }
  printf("%lld\n", cnt);
  return 0;
}
