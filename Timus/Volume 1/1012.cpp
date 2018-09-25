#include <bits/stdc++.h>

using namespace std;

const int N = 1800 + 5;
const int K = 10 + 5;

typedef vector<int> INT;

INT f[2][K];

void clear_zero(INT &a) {
  while (a.back() == 0 && a.size() > 1) {
    a.pop_back();
  }
}

void add(INT &a, INT &b) {
  int sz = max(a.size(), b.size());
  while ((int)a.size() < sz) {
    a.push_back(0);
  }
  while ((int)b.size() < sz) {
    b.push_back(0);
  }
  int r = 0;
  for (int i = 0; i < sz; i++) {
    a[i] += b[i] + r;
    r = a[i] / 10;
    a[i] %= 10;
  }
  if (r) {
    a.push_back(r);
  }
}

int main() {
  int n, K;
  scanf("%d %d", &n, &K);
  int t = 0;
  for (int i = 1; i < 10; i++) {
    f[t][i] = vector<int>(1, 1);
  }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < K; j++) {
      f[t^1][j] = vector<int>(1, 0);
    }
    for (int j = 0; j < K; j++) {
      for (int k = 0; k < K; k++) {
        if (j + k != 0) {
          add(f[t^1][k], f[t][j]);
        }
      }
    }
    t ^= 1;
  }
  INT ans = vector<int>(1, 0);
  for (int i = 0; i < K; i++) {
    add(ans, f[t][i]);
  }
  clear_zero(ans);
  for (int i = (int)ans.size() - 1; i >= 0; i--) {
    printf("%d", ans[i]);
  }
  printf("\n");
  return 0;
}
