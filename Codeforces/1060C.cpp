/*
Created 2018-10-07
"Maximum Subrectangle"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 2000 + 5;

int a, b;
int suma[N], sumb[N];

int min_sum(int *a, int len, int n) {
  int ret = 1e9;
  for (int i = len; i <= n; i++) {
    ret = min(ret, a[i] - a[i-len]);
  }
  return ret;
}

int main() {
  int n, m, x;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a);
    suma[i] = suma[i-1] + a;
  }
  for (int i = 1; i <= m; i++) {
    scanf("%d", &b);
    sumb[i] = sumb[i-1] + b;
  }
  scanf("%d", &x);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int a_sum = min_sum(suma, i, n);
    int l = 0, r = m+1;
    while (r - l > 1) {
      int mid = (l + r) / 2;
      int b_sum = min_sum(sumb, mid, m);
      if (1LL * a_sum * b_sum <= x) {
        l = mid;
      } else {
        r = mid;
      }
    }
    ans = max(ans, i * l);
  }
  printf("%d\n", ans);
  return 0;
}
