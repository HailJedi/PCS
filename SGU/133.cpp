#include <bits/stdc++.h>

using namespace std;

const int N = 16000 + 5;

pair<int, int> inter[N];
bool del[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &inter[i].first, &inter[i].second);
  }
  sort(inter+1, inter+1+n);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (!del[i]) {
      int p = i+1;
      while (p <= n && inter[p].second < inter[i].second) {
        del[p] = true;
        ans++;
        p++;
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}
