#include <bits/stdc++.h>

using namespace std;

const int N = 200 + 5;

char pas[N];
map<char, int> cnt, cnt2;

int main() {
  int n, a, b;
  cin >> n >> a >> b;
  if (a + b > n) {
    cout << -1 << endl;
    return 0;
  }
  cnt2['0'] = a, cnt2['1'] = b, cnt2['2'] = n - a - b;
  for (int i = 1; i <= n; i++) {
    cin >> pas[i];
    cnt[pas[i]]++;
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (cnt[pas[i]] > cnt2[pas[i]]) {
      for (int j = 0; j < 3; j++) {
        if (cnt[j+'0'] < cnt2[j+'0']) {
          cnt[pas[i]]--;
          pas[i] = j+'0';
          cnt[pas[i]]++;
          ans++;
          break;
        }
      }
    }
  }
  cout << ans << endl;
  for (int i = 1; i <= n; i++) {
    cout << pas[i];
  }
  return 0;
}
