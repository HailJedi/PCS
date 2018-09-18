#include <bits/stdc++.h>

using namespace std;

const int N = 500000 + 5;

int n;
char str[N];
set<int> st;

void solve(int len) {
  int bi = 0;
  for (int i = 0; i < len; i++) {
    bi |= ((str[i] == 'a') << i);
  }
  st.insert(bi);
  for (int i = len; i < n; i++) {
    bi >>= 1;
    bi |= ((str[i] == 'a') << (len-1));
    st.insert(bi);
  }
}

int main() {
  // freopen("read.in", "r", stdin);
  scanf("%d %s", &n, str);
  int l = 0, r = 20;
  while (r - l > 1) {
    int mid = (l + r) / 2;
    solve(mid);
    if (st.size() == (1 << mid)) {
      l = mid;
    } else {
      r = mid;
    }
    st.clear();
  }
  int ans = l + 1;
  solve(ans);
  printf("%d\n", ans);
  for (int i = 0; i < (1 << ans); i++) {
    if (!st.count(i)) {
      for (int j = 0; j < ans; j++) {
        printf("%c", (i >> j) & 1 ? 'a' : 'b');
      }
      printf("\n");
      break;
    }
  }
  return 0;
}
