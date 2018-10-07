/*
Created 2018-10-07
"Social Circles"
A greedy solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int n;
int l[N], r[N];

int main () {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &l[i], &r[i]);
  }
  sort(l+1, l+1+n);
  sort(r+1, r+1+n);
  long long ans = n;
  for (int i = 1; i <= n; i++) {
    ans += max(l[i], r[i]);
  }
  printf("%lld\n", ans);
  return 0;
}
