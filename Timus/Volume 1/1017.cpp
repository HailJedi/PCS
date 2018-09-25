#include <bits/stdc++.h>

using namespace std;

const int N = 500 + 5;

long long f[N][N];

int main() {
  int n;
  cin >> n;
  f[1][1] = 1;
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j*(j+1)/2 <= i; j++) {
      f[i][j] += f[i-j][j-1] + f[i-j][j];
    }
  }
  long long ans = 0;
  for (int i = 2; i <= n; i++) {
    ans += f[n][i];
  }
  cout << ans << endl;
  return 0;
}
