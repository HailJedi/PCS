/*
Created 2018-09-29
E. Vasya and Good Sequences
A brute force solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 300000 + 5;

int n;
long long a;
int b[N], cnt[N][2];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &a);
    b[i] = __builtin_popcountll(a);
  }
  cnt[n+1][0] = 1;
  int suf_sum = 0;
  long long ans = 0;
  for (int i = n; i >= 1; i--) {
    suf_sum += b[i];
    ans += cnt[i+1][suf_sum & 1];
    int mx = 0, sum = 0;
    for (int j = i; j <= i + 64 && j <= n; j++) {
      mx = max(mx, b[j]);
      sum += b[j];
      ans -= ((sum & 1) == 0 && mx > sum / 2);
    }
    cnt[i][0] = cnt[i+1][0];
    cnt[i][1] = cnt[i+1][1];
    cnt[i][suf_sum & 1]++;
  }
  printf("%lld\n", ans);
  return 0;
}
