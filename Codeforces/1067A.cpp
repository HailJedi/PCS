/*
Created 2018-11-04
"Array Without Local Maximums"
*/

#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;
const int N = 100000 + 5;
const int A = 200 + 5;

long long f[2][A][2];
int a[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  int t = 0;
  for (int i = 1; i <= 200; i++) {
    if (a[1] == -1 || a[1] == i) {
      f[t][i][1] = 1;
    }
  }
  for (int i = 2; i <= n; i++) {
    t ^= 1;
    for (int j = 1; j <= 200; j++) {
      (f[t^1][j][0] += f[t^1][j-1][0]) %= mod;
      (f[t^1][j][1] += f[t^1][j-1][1]) %= mod;
    }
    for (int j = 1; j <= 200; j++) {
      if (a[i] == -1 || a[i] == j) {
        f[t][j][0] = (f[t^1][200][0] - f[t^1][j-1][0] + f[t^1][j][1] - f[t^1][j-1][1]) % mod;
        f[t][j][1] = (f[t^1][j-1][0] + f[t^1][j-1][1]) % mod;
      } else {
        f[t][j][0] = f[t][j][1] = 0;
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= 200; i++) {
    if (a[n] == -1 || a[n] == i) {
      (ans += f[t][i][0]) %= mod;
    }
  }
  (ans += mod) %= mod;
  printf("%d\n", ans);
  return 0;
}
