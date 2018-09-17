#include <bits/stdc++.h>

using namespace std;

const int N = 65536 + 5;

int bit[N];

int lowbit(int x) {
  return x & -x;
}

void add(int p) {
  for (; p < N; p += lowbit(p)) {
    bit[p]++;
  }
}

int sum(int p) {
  int ret = 0;
  for (; p; p -= lowbit(p)) {
    ret += bit[p];
  }
  return ret;
}

pair<int, int> num[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &num[i].first);
    num[i].second = i;
  }
  sort(num+1, num+1+n);
  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += sum(N-1) - sum(num[i].second);
    add(num[i].second);
  }
  printf("%lld\n", ans);
  return 0;
}
