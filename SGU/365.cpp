#include <bits/stdc++.h>

using namespace std;

const int N = 20 + 5;

long long f[N][10];

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < 10; i++) {
    f[1][i] = 1;
  }
  f[0][0] = 1;
  for (int i = 2; i <= n; i++) {
    for (int j = 0; j < 10; j++) {
      for (int k = 0; k <= j; k++) {
        f[i][j] += f[i-1][k];
      }
    }
  }
  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 10; j++) {
      for (int k = 0; k < j; k++) {
        ans += f[i][j] * f[n-i][k];
      }
    }
  }
  cout << ans + 1 << endl;
  return 0;
}
