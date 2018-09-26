#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int n;
int a[N], idx[N];
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

bool cmp(int x, int y) {
  return a[x] < a[y];
}

int main() {
  freopen("sort.in", "r", stdin);
  freopen("sort.out", "w", stdout);
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    idx[i] = i;
  }
  sort(idx+1, idx+1+n, cmp);
  int ans = 1;
  for (int i = 1; i < n; i++) {
    add(idx[i]);
    ans = max(ans, i - sum(i));
  }
  printf("%d\n", ans);
  return 0;
}
