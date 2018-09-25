#include <bits/stdc++.h>

using namespace std;

int main() {
  int s, n;
  scanf("%d %d", &n, &s);
  double yes = s - 2 * n, no = 3 * n - s;
  printf("%.7lf\n", n - (yes * yes + no * (no - 1)) / n);
  return 0;
}
