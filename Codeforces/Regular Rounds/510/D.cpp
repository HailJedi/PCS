#include <bits/stdc++.h>

using namespace std;

const int N = 200000 + 5;

long long a[N], s[N];
long long t;
int n;

int bit[N];

int lowbit(int x) {
  return x & -x;
}

void add(int p) {
  for (; p < N; p += lowbit(p)) {
    bit[p]++;
  }
}

long long sum(int p) {
  int ret = 0;
  for (; p; p -= lowbit(p)) {
    ret += bit[p];
  }
  return ret;
}

vector<long long> vec;
int id(long long x) {
  return upper_bound(vec.begin(), vec.end(), x) - vec.begin();
}

int main() {
  scanf("%d %lld", &n, &t);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &a[i]);
    s[i] = s[i-1] + a[i];
    vec.push_back(s[i]);
  }
  vec.push_back(-1e18);
  vec.push_back(0);
  sort(vec.begin(), vec.end());
  unique(vec.begin(), vec.end());
  long long ans = 0;
  int m = vec.size() + 1;
  add(id(0)-1);
  for (int i = 1; i <= n; i++) {
    int j = id(s[i]-t);
    ans += sum(m) - sum(j-1);
    add(id(s[i])-1);
  }
  printf("%lld\n", ans);
  return 0;
}
