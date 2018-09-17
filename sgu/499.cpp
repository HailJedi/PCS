#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const int V = 1000000 + 5;

int cnt[V], fac[V];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int v;
    scanf("%d", &v);
    cnt[v]++;
  }
  for (int i = 2; i < V; i++) {
    for (int j = i; j < V; j += i) {
      fac[i] += cnt[j];
    }
  }
  for (int i = V-1; i >= 2; i--) {
    if (fac[i] >= 2) {
      printf("%d\n", i);
      break;
    }
  }
  return 0;
}
