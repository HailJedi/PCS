#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;
const int mod = 1e9 + 7;

long long s[N];

int main() {
  freopen("spainting.in", "r", stdin);
  freopen("spainting.out", "w", stdout);
  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 1; i < k; i++) {
    s[i] = (m * s[i-1] + m) % mod;
  }
  for (int i = k; i <= n; i++) {
    s[i] = (m * s[i-1] % mod - (m-1) * s[i-k] % mod + mod) % mod;
  }
  long long p = 1;
  for (int i = 1; i <= n; i++) {
    p = p * m % mod;
  }
  cout << (((p - s[n] + s[n-1]) % mod) + mod) % mod << endl;
  return 0;
}
