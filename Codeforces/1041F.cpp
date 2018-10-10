/*
Created 2018-10-10
"Ray in the tube"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int n, m, y;
int A[N], B[N];

int main() {
  scanf("%d %d", &n, &y);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &A[i]);
  }
  scanf("%d %d", &m, &y);
  for (int i = 1; i <= m; i++) {
    scanf("%d", &B[i]);
  }
  int ans = 0;
  for (long long T = 2; T <= 2e9; T *= 2) {
    map<int, int> cnt;
    for (int i = 1; i <= n; i++) {
      cnt[A[i] % T]++;
    }
    for (int i = 1; i <= m; i++) {
      cnt[(B[i] + T/2) % T]++;
    }
    for (map<int, int>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
      ans = max(ans, it->second);
    }
  }
  map<int, int> cnt;
  for (int i = 1; i <= n; i++) {
    cnt[A[i]]++;
  }
  for (int i = 1; i <= m; i++) {
    ans = max(ans, 1 + cnt[B[i]]);
  }
  printf("%d\n", ans);
  return 0;
}
