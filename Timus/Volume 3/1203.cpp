#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

struct Lecture {
  int s, t;
  Lecture() {}
  bool operator < (const Lecture &L) const {
    if (t != L.t) {
      return t < L.t;
    } 
    return s < L.s;
  }
} lec[N];

int mx[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &lec[i].s, &lec[i].t);
  }
  sort(lec+1, lec+1+n);
  memset(mx, -1, sizeof mx);
  mx[0] = 0;
  int f, ans = 0, idx = 0;
  for (int i = 1; i <= n; i++) {
    while (idx < n && lec[idx+1].t < lec[i].s) {
      idx++;
    }
    f = mx[idx] + 1;
    ans = max(ans, f);
    mx[i] = max(mx[i-1], f);
  }
  printf("%d\n", ans);
  return 0;
}
