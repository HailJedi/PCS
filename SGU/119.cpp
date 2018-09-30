#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, a, b;
  scanf("%d %d %d", &n, &a, &b);
  vector< pair<int, int> > vec;
  a %= n;
  b %= n;
  for (int i = a, j = b, f = 1; i != a || j != b || f; (i += a) %= n, (j += b) %= n, f = 0) {
    vec.push_back(make_pair(i, j));
  }
  sort(vec.begin(), vec.end());
  printf("%d\n", (int)vec.size());
  for (int i = 0; i < vec.size(); i++) {
    printf("%d %d\n", vec[i].first, vec[i].second);
  }
  return 0;
}
