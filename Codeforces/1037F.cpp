/*
Created 2018-10-15
"Maximum Reduction"
A counting on segment problem
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;
const int mod = 1000000007;

int n, k;
int a[N], l[N], r[N];

int norm(long long x) {
  ((x %= mod) += mod) %= mod;
  return x;
}

int solve(int l, int r) {
  if (l > r || r - l + 1 < k) {
    return 0;
  }
  int p = r - l + 2 - k, f = p / (k - 1);
  return norm(1LL * p * (f + 1) % mod - 1LL * (f + 1) * f / 2 % mod * (k - 1) % mod);
}

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  stack<pair<int, int>> stk;
  for (int i = 1; i <= n; i++) {
    l[i] = i;
    while (!stk.empty() && stk.top().first < a[i]) {
      l[i] = stk.top().second;
      stk.pop();
    }
    stk.push(make_pair(a[i], l[i]));
  }
  while (!stk.empty()) {
    stk.pop();
  }
  for (int i = n; i >= 1; i--) {
    r[i] = i;
    while (!stk.empty() && stk.top().first <= a[i]) {
      r[i] = stk.top().second;
      stk.pop();
    }
    stk.push(make_pair(a[i], r[i]));
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int freq = norm(1LL * solve(l[i], r[i]) - 1LL * solve(l[i], i-1) - 1LL * solve(i+1, r[i]));
    ans = norm(ans + 1LL * freq * a[i]);
  }
  printf("%d\n", ans);
  return 0;
}
