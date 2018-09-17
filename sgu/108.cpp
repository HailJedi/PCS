#include <bits/stdc++.h>

using namespace std;

const int N = 10000000 + 5;
const int K = 5000 + 5;

bool not_self[N];
int s[K];

int dig_sum(int x) {
  int ret = 0;
  while (x) {
    ret += x % 10;
    x /= 10;
  }
  return ret;
}

int main() {
  // freopen("read.in", "r", stdin);
  // freopen("write.out", "w", stdout);
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= k; i++) {
    scanf("%d", &s[i]);
  }
  vector<int> self;
  for (int i = 1; i <= n; i++) {
    if (!not_self[i]) {
      self.push_back(i);
      for (int j = i + dig_sum(i); !not_self[j] && j <= n; j += dig_sum(j)) {
        not_self[j] = true;
      }
    }
  }
  printf("%d\n", self.size());
  for (int i = 1; i <= k; i++) {
    printf("%d ", self[s[i]-1]);
  }
  printf("\n");
  return 0;
}
