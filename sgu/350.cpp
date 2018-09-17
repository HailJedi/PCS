#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;

int b[N];
int m;
set<int> st;

int main() {
  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> b[i];
    st.insert(b[i]);
  }
  vector<int> pre;
  for (int i = 2; i <= m; i++) {
    if (st.count(b[1] ^ b[i])) {
      pre.push_back(b[i]);
    }
  }
  vector<int> ans;
  ans.push_back(0);
  ans.push_back(b[1]);
  if (pre.size()) {
    ans.push_back(pre[0]);
  }
  for (int i = 1; i < pre.size(); i++) {
    if (st.count(pre[i] ^ pre[0]) && pre[i] != (b[1] ^ pre[0])) {
      ans.push_back(pre[i]);
    }
  }
  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i] << ' ';
  }
  cout << endl;
  return 0;
}
