#include <bits/stdc++.h>

using namespace std;

const int N = 45 + 5;

long long f[N][3][3];

int main() {
  int n;
  scanf("%d", &n);
  if (n <= 2) {
    printf("2\n");
  } else {
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 3; j++) {
        if (i != j) {
          f[2][i][j] = 1;
        }
      }
    }
    for (int i = 2; i <= n; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          for (int l = 0; l < 3; l++) {
            if (j != k && k != l && (k != 2 || (k == 2 && j + l == 1))) {
              f[i+1][k][l] += f[i][j][k];
            }
          }
        }
      }
    }
    long long ans = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 2; j++) {
        ans += f[n][i][j];
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
