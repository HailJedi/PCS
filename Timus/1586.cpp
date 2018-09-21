#include <bits/stdc++.h>

using namespace std;

const int N = 10000 + 5;
const int MOD = 1e9 + 9;
const int K = 1000 + 5;

bool is_prime[K];

void calc_prime() {
  memset(is_prime, true, sizeof is_prime);
  for (int i = 2; i < K; i++) {
    if (is_prime[i]) {
      for (int j = 2 * i; j < K; j += i) {
        is_prime[j] = false;
      }
    }
  }
}

int f[2][10][10][10];

int main() {
  calc_prime();
  int n;
  cin >> n;
  int t = 0;
  vector<int> p;
  for (int i = 100; i < 1000; i++) {
    int d1 = i / 100, d2 = i % 100 / 10, d3 = i % 10;
    if (is_prime[i]) {
      f[t][d1][d2][d3] = 1;
      p.push_back(i);
    }
  }
  for (int i = 3; i < n; i++) {
    memset(f[t^1], 0, sizeof f[t^1]);
    for (int j = 0; j < (int)p.size(); j++) {
      int prime = p[j];
      int d1 = prime / 100, d2 = prime % 100 / 10, d3 = prime % 10;
      if (f[t][d1][d2][d3] != 0 && d2 != 0) {
        for (int d4 = 0; d4 < 10; d4++) {
          if (is_prime[d2 * 100 + d3 * 10 + d4]) {
            (f[t^1][d2][d3][d4] += f[t][d1][d2][d3]) %= MOD;
          }
        }
      }
    }
    t ^= 1;
  }
  int ans = 0;
  for (int d1 = 1; d1 < 10; d1++) {
    for (int d2 = 0; d2 < 10; d2++) {
      for (int d3 = 0; d3 < 10; d3++) {
        (ans += f[t][d1][d2][d3]) %= MOD;
      }
    }
  }
  cout << ans << endl;
  return 0;
}
