#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;

int cnt[N];
int a[N];
char ans[N];

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    cnt[a[i]]++;
  }
  int single = 0, pair = 0;
  for (int i = 1; i < N; i++) {
    if (cnt[i] == 1) {
      single++;
    } else
    if (cnt[i] > 2) {
      pair++;
    }
  }
  if ((single & 1) == 0 || ((single & 1) && pair > 0)) {
    printf("YES\n");
    if (single & 1) {
      int re = -1;
      for (int i = 1; i <= n; i++) {
        if (re == -1 && cnt[a[i]] > 2) {
          ans[i] = 'B';
          re = i;
        } else
        if (a[i] == a[re]) {
          ans[i] = 'A';
        }
      }
    }
    int toA = (single + 1) / 2;
    for (int i = 1; i <= n && toA; i++) {
      if (cnt[a[i]] == 1) {
        ans[i] = 'A';
        toA--;
      }
    }
    int toB = single / 2;
    for (int i = 1; i <= n && toB; i++) {
      if (cnt[a[i]] == 1 && ans[i] != 'A' && ans[i] != 'B') {
        ans[i] = 'B';
        toB--;
      }
    }
    for (int i = 1; i <= n; i++) {
      if (ans[i] != 'A' && ans[i] != 'B') {
        ans[i] = 'A';
      }
    }
    for (int i = 1; i <= n; i++) {
      printf("%c", ans[i]);
    }
    printf("\n");
  } else {
    printf("NO\n");
  }
  return 0;
}
