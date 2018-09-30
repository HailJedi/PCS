#include <bits/stdc++.h>

using namespace std;

const int N = 200000 + 5;

int a[N];
bool del[N];

int main() {
  int n;
  scanf("%d", &n);
  int f = 1, ngp = -1;
  vector<int> zps, nps;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    f *= (a[i] >= 0 ? 1 : -1);
    if (a[i] < 0 && (ngp == -1 || a[i] > a[ngp])) {
      ngp = i;
    }
    if (a[i] == 0) {
      zps.push_back(i);
    }
    if (a[i] < 0) {
      nps.push_back(i);
    }
  }
  if (n == 1) {
    return 0;
  }
  if (zps.size() || f < 0) {
    if (f < 0) {
      zps.push_back(ngp);
      if (zps.size() > 1) {
        swap(zps.back(), zps[zps.size()-2]);
      }
    }
    if ((int)zps.size() == n) {
      zps.pop_back();
    }
    for (int i = 0; i < (int)zps.size(); i++) {
      if (i != (int)zps.size()-1) {
        printf("1 %d %d\n", zps[i], zps[i+1]);
        del[zps[i]] = del[zps[i+1]] = true;
      }
    }
    del[zps.back()] = true;
    printf("2 %d\n", zps.back());
    for (int i = 1; i < n; i++) {
      if (del[i]) {
        continue;
      }
      int j = i + 1;
      while (j <= n && del[j]) {
        j++;
      }
      if (j <= n) {
        printf("1 %d %d\n", i, j);
      }
    }
  } else {
    for (int i = 1; i < n; i++) {
      printf("1 %d %d\n", i, i+1);
    }
  }
}
