#include <bits/stdc++.h>

using namespace std;

const int K = 100;
const int T = 100000 + 5;
const long long INF = 3e18;

int mu[K];
bool is_prime[K];
int root[K];

void calc_mu() {
  for (int i = 1; i < K; i++) {
    mu[i] = 1;
    is_prime[i] = true;
  }
  for (int i = 2; i < K; i++) {
    if (is_prime[i]) {
      mu[i] = -1;
      for (int j = i*2; j < K; j += i) {
        is_prime[j] = false;
        if ((j / i) % i == 0) {
          mu[j] = 0;
        } else {
          mu[j] *= -1;
        }
      }
    }
  }
}

long long ans[T];

long long POW(long long a, int n) {
  long long b = 1;
  while (n) {
    if (n & 1) {
      if (b < INF / a) {
        b *= a;
      } else {
        return INF;
      }
    }
    if (n > 1) {
      if (a < INF / a) {
        a *= a;
      } else {
        return INF;
      }
    }
    n >>= 1;
  }
  return b;
}

long long solve(long long n) {
  int pw = 63 - __builtin_clzll(n);
  for (int i = 3; i <= pw; i++) {
    if (mu[i]) {
      while (POW(root[i], i) > n) {
        root[i]--;
      }
    }
  }
  long long ret = n-1;
  for (int i = 2; i <= pw; i++) {
    ret += mu[i] * (root[i] - 1);
  }
  return ret;
}

int main() {
  calc_mu();
  int T;
  scanf("%d", &T);
  vector< pair<long long, int> > q;
  for (int i = 1; i <= T; i++) {
    long long n;
    scanf("%lld", &n);
    q.push_back(make_pair(n, i));
  }
  sort(q.begin(), q.end(), greater< pair<long long, int> >());
  root[3] = 1000000;
  root[4] = 31622;
  root[5] = 3981;
  for (int i = 6; i < K; i++) {
    root[i] = 1000;
  }
  for (int i = 0; i < T; i++) {
    long long n = q[i].first;
    root[2] = (int)sqrt(n);
    ans[q[i].second] = solve(n);
  }
  for (int i = 1; i <= T; i++) {
    printf("%lld\n", ans[i]);
  }
  return 0;
}
