#include <bits/stdc++.h>

using namespace std;

const int N = 10;
const int K = N * N;

int n, k;
long long f[N+1][K+1][1<<N];

inline int shl(int x) {
  return 1 << x;
}

void dfs(int row, int cnt, const int ps, int s, int p, const long long &dp) {
  if (p == n+1) {
    f[row][cnt][s>>1] += dp;
  } else {
    dfs(row, cnt, ps, s, p+1, dp);
    if (!((ps & shl(p+1)) | (ps & shl(p)) | (ps & shl(p-1)) | (s & (shl(p-1)))) && cnt < k) {
      dfs(row, cnt+1, ps, s | shl(p), p+1, dp);
    }
  }
}

int main() {
  cin >> n >> k;
  f[0][0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= k; j++) {
      for (int s = 0; s < shl(n); s++) {
        if (f[i][j][s]) {
          dfs(i+1, j, s<<1, 0, 1, f[i][j][s]);
        }
      }
    }
  }
  long long ans = 0;
  for (int s = 0; s < shl(n); s++) {
    ans += f[n][k][s];
  }
  cout << ans << endl;
  return 0;
}
