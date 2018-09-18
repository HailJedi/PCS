#include <bits/stdc++.h>

using namespace std;

const int N = 10000 + 5;
const int M = 100000 + 5;

int cnt[N];

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    cnt[u]++;
    cnt[v]++;
  }
  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += cnt[i] * cnt[i];
  }
  printf("%lld\n", ans);
  return 0;
}
