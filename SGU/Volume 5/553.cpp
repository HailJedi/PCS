#include <bits/stdc++.h>

using namespace std;

const int N = 200000 + 5;

int w[N], c[N];
int sum_w[N], sum_c[N];

bool update(int &x, int y) {
  if (x < y) {
    x = y;
    return true;
  }
  return false;
}

int main() {
  int n, m, k;
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &w[i], &c[i]);
    sum_w[i] = sum_w[i-1] + w[i];
    sum_c[i] = sum_c[i-1] + c[i];
  }
  if (n == 1) {
    cout << 1 << ' ' << w[1] << endl;
    cout << "T" << endl;
    return 0;
  }
  int ans = 0, T = 0, H = 0, p = 0;
  while (p < n-m && (sum_w[n-m]-sum_w[p])*k >= sum_w[n]-sum_w[n-m]) {
    p++;
  }
  for (int l = n-m+1; l >= 1 && p; l--) {
    int r = l + m - 1;
    while (p > 0 && (sum_w[l-1]-sum_w[p-1]) * k < sum_w[r]-sum_w[l-1]) {
      p--;
    }
    if (p > 0 && update(ans, sum_c[n]-sum_c[r]+sum_c[p-1])) {
      T = p-1, H = n-r;
    }
  }
  printf("%d %d\n", T + H, ans);
  while (H--) {
    printf("H");
  }
  while (T--) {
    printf("T");
  }
  printf("\n");
  return 0;
}
