#include <bits/stdc++.h>

using namespace std;

int main() {
  freopen("read.in", "w", stdout);
  srand(time(NULL));
  int n, k, p;
  k = 400, n = 600, p = 233333;
  printf("%d %d %d\n", n, k, p);
  for (int i = 1; i <= k; i++) {
    printf("%d ", rand() % 600 + 1);
  }
  puts("");
  for (int i = 1; i <= n; i++) {
    printf("%d %d\n", rand() % 600 + 1, rand() % k + 1);
  }
  puts("");
  return 0;
}
