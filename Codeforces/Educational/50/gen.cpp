#include <bits/stdc++.h>

using namespace std;

int main() {
  freopen("read.in", "w", stdout);
  srand(time(NULL));
  printf("1000\n");
  for (int T = 1; T <= 1000; T++) {
    long long rd = rand();
    rd <<= 16;
    rd |= rand();
    printf("%lld\n", rd);
  }
  return 0;
}
