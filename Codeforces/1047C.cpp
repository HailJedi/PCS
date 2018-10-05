/*
Created 2018-10-05
"Enlarge GCD"
An Euler sieve solution
*/

#include <bits/stdc++.h>

using namespace std;

const int A = 15000000 + 5;
const int N = 300000 + 5;

int gcd(int a, int b) {
  return !b ? a : gcd(b, a % b);
}

int a[N];
int v[A], cnt[A];

int main() {
  vector<int> prime;
  for (int i = 2; i < A; i++) {
    if (v[i] == 0) {
      v[i] = i;
      prime.push_back(i);
    }
    for (auto p: prime) {
      if (p > v[i] || p * i >= A) {
        break;
      }
      v[p * i] = p;
    }
  }
  int n, g = -1;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    if (g == -1) {
      g = a[i];
    } else {
      g = gcd(a[i], g);
    }
  }
  for (int i = 1; i <= n; i++) {
    a[i] /= g;
    while (a[i] > 1) {
      cnt[v[a[i]]]++;
      int rec = v[a[i]];
      a[i] /= v[a[i]];
      while (a[i] > 1 && v[a[i]] == rec){
        a[i] /= v[a[i]];
      }
    }
  }
  int ans = n;
  for (int i = 2; i < A; i++) {
    ans = min(ans, n - cnt[i]);
  }
  if (ans == n) {
    printf("-1\n");
  } else {
    printf("%d\n", ans);
  }
  return 0;
}
