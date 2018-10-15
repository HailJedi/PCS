/*
Created 2018-10-15
"Equalize"
A dp solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;
const int INF = 0x3f3f3f3f;

int n;
char A[N], B[N];
int f[N][2];

void update(int &x, int y) {
  if (x > y) {
    x = y;
  }
}

int main() {
  scanf("%d %s %s", &n, A+1, B+1);
  memset(f, INF, sizeof f);
  f[1][0] = A[1] == '1';
  f[1][1] = A[1] == '0';
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < 2; j++) {
      if (f[i][j] != INF) {
        if (B[i]-'0' == j) {
          update(f[i+1][0], f[i][j] + (A[i+1] == '1'));
          update(f[i+1][1], f[i][j] + (A[i+1] == '0'));
        }
        if (A[i+1] == B[i]) {
          update(f[i+1][j], f[i][j] + 1);
        }
      }
    }
  }
  printf("%d\n", f[n][B[n]-'0']);
  return 0;
}
