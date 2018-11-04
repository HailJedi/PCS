/*
Created 2018-11-04
"扑克牌"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;

int f[N];

int main() {
  freopen("test.in", "r", stdin);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    for (int i = n; i >= a; i--) {
      f[i] = max(f[i], f[i-a] + b);
    }
  }
  printf("%d\n", f[n]);
}
