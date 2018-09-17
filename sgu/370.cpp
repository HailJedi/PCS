#include <bits/stdc++.h>

#pragma GCC optimize(2)

using namespace std;

const int N = 1000000 + 5;
const int B = (1 << 8);

vector<int> fac[N];
vector<int> dig[B];

bool not_prime[N];

int main() {
  int n, m;
  cin >> n >> m;
  if (n == 1 || m == 1) {
    cout << (n == m ? 0 : 1) << endl;
    return 0;
  }
  n--, m--;
  for (int i = 1; i < B; i++) {
    for (int j = 0; j < 8; j++) {
      if ((i >> j) & 1) {
        dig[i].push_back(j);
      }
    }
  }
  for (int i = 2; i <= n; i++) {
    if (!not_prime[i]) {
      fac[i].push_back(i);
      for (int j = 2*i; j <= n; j += i) {
        fac[j].push_back(i);
        not_prime[j] = true;
      }
    }
  }
  long long ans = m + 2;
  for (int i = 2; i <= n; i++) {
    long long cnt = m;
    int fn = fac[i].size();
    for (int j = 1; j < (1 << fn); j++) {
      long long prod = 1;
      int dn = dig[j].size();
      for (int k = 0; k < dn; k++) {
        int d = dig[j][k];
        prod *= fac[i][d];
      }
      if (dn & 1) {
        cnt -= m / prod;
      } else {
        cnt += m / prod;
      }
    }
    ans += cnt;
  }
  printf("%lld\n", ans);
  return 0;
}
