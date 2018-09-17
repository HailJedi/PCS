#include <bits/stdc++.h>

using namespace std;

const int N = 200 + 5;
const int X = 10000 + 5;

int cnt[X];
int a[N];
bool L[N][X], R[N][X];

int main() {
  int n, x;
  scanf("%d %d", &n, &x);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  L[0][0] = R[n+1][0] = true;
  for (int j = 0; j <= x; j++) {
    for (int i = 1; i <= n; i++) {
      L[i][j] |= L[i-1][j];
      if (j+a[i] <= x) {
        L[i][j+a[i]] |= L[i-1][j];
      }
    }
    for (int i = n; i >= 1; i--) {
      R[i][j] |= R[i+1][j];
      if (j+a[i] <= x) {
        R[i][j+a[i]] |= R[i+1][j];
      }
    }
  }
  vector<int> ans;
  for (int i = 1; i <= n; i++) {
    bool ok = true;
    for (int j = 0; j <= x && ok; j++) {
      if (L[i-1][j] && R[i+1][x-j]) {
        ok = false;
      }
    }
    if (ok) {
      ans.push_back(a[i]);
    }
  }
  printf("%d\n", (int)ans.size());
  for (int i = 0; i < ans.size(); i++) {
    printf("%d ", ans[i]);
  }
  printf("\n");
  return 0;
}
