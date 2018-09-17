#include <bits/stdc++.h>

using namespace std;

const int N = 200000 + 5;

int main() {
  int n;
  scanf("%d", &n);
  int d, ans = 0;
  priority_queue< pair<int, int> > q;
  for (int i = 2; i <= n; i++) {
    char s[10];
    scanf("%s %d", s, &d);
    if (s[0] == 'p') {
      while (i != n && (int)q.size() >= d) {
        ans += q.top().first;
        q.pop();
      }
    } else {
      ans += d;
      q.push(make_pair(-d, i));
    }
  }
  if ((int)q.size() < d) {
    printf("-1\n");
  } else {
    printf("%d\n%d\n", ans, (int)q.size());
    priority_queue<int> q2;
    while (!q.empty()) {
      q2.push(-q.top().second);
      q.pop();
    }
    while (!q2.empty()) {
      printf("%d ", -q2.top());
      q2.pop();
    }
  }
  return 0;
}
