#include <bits/stdc++.h>

using namespace std;

const int N = 20;

long long f[N][N];

int main() {
  int n, K;
  cin >> n >> K;
  for (int i = 1; i < 10; i++) {
    f[1][i] = 1;
  }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < K; j++) {
      for (int k = 0; k < K; k++) {
        if (j + k != 0) {
          f[i+1][k] += f[i][j];
        }
      }
    }
  }
  long long ans = 0;
  for (int i = 0; i < K; i++) {
    ans += f[n][i];
  }
  cout << ans << endl;
  return 0;
}
