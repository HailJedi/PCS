#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int n;
int a[N];

bool solve_mono(int f) {
  vector<int> vec1, vec2;
  vec1.push_back(a[1] * f);
  for (int i = 2; i <= n; i++) {
    if (a[i] * f > vec1.back()) {
      vec1.push_back(a[i] * f);
    } else
    if (vec2.empty() || a[i] * f > vec2.back()) {
      vec2.push_back(a[i] * f);
    } else {
      return false;
    }
  }
  if (vec2.empty()) {
    vec2.push_back(vec1.back());
    vec1.resize(vec1.size() - 1);
  }
  printf("%d %d\n", (int)vec1.size(), (int)vec2.size());
  for (int i = 0; i < (int)vec1.size(); i++) {
    printf("%d ", vec1[i] * f);
  }
  printf("\n");
  for (int i = 0; i < (int)vec2.size(); i++) {
    printf("%d ", vec2[i] * f);
  }
  printf("\n");
  return true;
}

int f[N], g[N];
int up_path[N], down_path[N];
bool use[N];
int fans[N], gans[N];

bool solve_cross() {
  for (int i = 1; i <= n; i++) {
    f[i] = 0;
    g[i] = N;
  }
  f[1] = N, g[1] = 0;
  for (int i = 2; i <= n; i++) {
    if (a[i] > a[i-1]) {
      f[i] = f[i-1];
      up_path[a[i]] = a[i-1];
    }
    if (a[i] < a[i-1]) {
      g[i] = g[i-1];
      down_path[a[i]] = a[i-1];
    }
    if (a[i] > g[i-1] && a[i-1] > f[i]) {
      f[i] = a[i-1];
      up_path[a[i]] = g[i-1];
    }
    if (a[i] < f[i-1] && a[i-1] < g[i]) {
      g[i] = a[i-1];
      down_path[a[i]] = f[i-1];
    }
  }
  if (f[n] == 0 && g[n] == N) {
    return false;
  }
  int fn = 0, gn = 0;
  if (f[n] == 0) {
    for (int i = a[n]; i != 0 && i != N; i = down_path[i]) {
      gans[++gn] = i;
      use[i] = true;
    }
    printf("%d %d\n", gn, n - gn);
    while (gn) {
      printf("%d ", gans[gn--]);
    }
    printf("\n");
  } else {
    for (int i = a[n]; i != 0 && i != N; i = up_path[i]) {
      fans[++fn] = i;
      use[i] = true;
    }
    printf("%d %d\n", fn, n - fn);
    while (fn) {
      printf("%d ", fans[fn--]);
    }
    printf("\n");
  }
  for (int i = 1; i <= n; i++) {
    if (!use[a[i]]) {
      printf("%d ", a[i]);
    }
  }
  printf("\n");
  return true;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  if (!solve_mono(1) && !solve_mono(-1) && !solve_cross()) {
    printf("Fail\n");
  }
  return 0;
}
