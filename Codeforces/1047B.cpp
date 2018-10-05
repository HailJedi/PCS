/*
Created 2018-10-05
"Cover Points"
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, x, y, ans = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &x, &y);
    ans = max(ans, x + y);
  }
  printf("%d\n", ans);
  return 0;
}
