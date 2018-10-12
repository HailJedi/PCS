/*
Created 2018-10-11
"Subway Pursuit"
A binary search problem
*/

#include <bits/stdc++.h>

using namespace std;

bool query(long long l, long long r) {
  cout << l << ' ' << r << endl;
  cout.flush();
  string res;
  cin >> res;
  if (res == "Yes" && l == r) {
    exit(0);
  }
  return res == "Yes";
}

int main() {
  srand(time(0));
  long long n, k, l, r;
  cin >> n >> k;
  l = 1, r = n;
  while (true) {
    long long len = r - l + 1;
    if (len >= (k+1) << 2) {
      long long mid = (l + r) / 2;
      if (query(l, mid)) {
        r = mid;
      } else {
        l = mid+1;
      }
    } else {
      int p = rand() % len;
      query(l+p, l+p);
    }
    l = max(1LL, l-k);
    r = min(n, r+k);
  }
  return 0;
}
