#include <bits/stdc++.h>

using namespace std;

const int N = 45;

long long f[N];
vector<long long> fibo_sum;
long long n, k, sum;

int main() {
  f[0] = 1;
  f[1] = 1;
  f[2] = 1;
  for (int i = 0; i < 3; i++) {
    fibo_sum.push_back(i+1);
  }
  sum = 3;
  for (int i = 3; i < N; i++) {
    f[i] = f[i-1] + f[i-2];
    sum += f[i];
    fibo_sum.push_back(sum);
  }
  while (cin >> n >> k) {
    if (k > fibo_sum[n]) {
      printf("-1\n");
      continue;
    }
    long long ans = 0;
    while (k > 1) {
      int dig = lower_bound(fibo_sum.begin(), fibo_sum.end(), k) - fibo_sum.begin();
      ans |= (1LL << (dig-1));
      k -= fibo_sum[dig-1];
    }
    for (int i = n-1; i >= 0; i--) {
      cout << ((ans >> i) & 1LL);
    }
    cout << endl;
  }
  return 0;
}
