#include <bits/stdc++.h>

using namespace std;

const int N = 11;
const int K = N * N;

long long f[2][2*N][N];
int tem[2*N];
int row[2], n, k;

void solve(int x) {
  for (int i = x+1; i <= n; i += 2) {
    tem[++row[x]] = i;
    if (i != n) {
      tem[++row[x]] = i;
    }
  }
  f[x][0][0] = 1;
  for (int i = 1; i <= row[x]; i++) {
    for (int j = 0; j <= tem[i] && j <= k; j++) {
      f[x][i][j] = f[x][i-1][j] + f[x][i-1][j-1] * (tem[i] - j + 1);
    }
  }
}

int main() {
  cin >> n >> k;
  solve(0);
  solve(1);
  long long ans = 0;
  for (int i = 0; i <= k; i++) {
    ans += f[0][row[0]][i] * f[1][row[1]][k-i];
  }
  cout << ans << endl;
  return 0;
}
