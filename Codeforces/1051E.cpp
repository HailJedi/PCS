/*
Created 2018-09-29
E. Vasya and Big Integers
A Z-function solution
*/

#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;
const int N = 2000000 + 5;

int zl[N], zr[N];

void make_z_function(int *z, const string &str) {
  int L = 0, R = 0, n = str.length();
  for (int i = 1; i < n; i++) {
    if (i > R) {
      L = R = i;
    } else {
      int k = i - L;
      if (z[k] < R-i+1) {
        z[i] = z[k];
        continue;
      }
      L = i;
    }
    while (R < n && str[R] == str[R-L]) {
      R++;
    }
    z[i] = R - L;
    R--;
  }
}

string s, l, r;

int add(int x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
  return x;
}

int f[N], sum[N];
int n;

int cmp(int *z, string &t, int pos) {
  int len = t.length();
  if (n - pos < len) {
    return -1;
  }
  int x = z[len+1+pos];
  if (x == len) {
    return 0;
  }
  return s[pos + x] < t[x] ? -1 : 1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> s >> l >> r;
  make_z_function(zl, l + "#" + s);
  make_z_function(zr, r + "#" + s);
  n = s.length();
  f[n] = sum[n] = 1;
  for (int i = n-1; i >= 0; i--) {
    if (s[i] == '0') {
      if (l == "0") {
        f[i] = f[i+1];
      } else {
        f[i] = 0;
      }
    } else {
      int L = i + l.length();
      int R = i + r.length();
      if (cmp(zl, l, i) < 0) {
        L++;
      }
      if (cmp(zr, r, i) > 0) {
        R--;
      }
      if (L <= R && L <= n) {
        f[i] = sum[L];
        if (R < n) {
          f[i] = add(f[i], mod - sum[R+1]);
        }
      }
    }
    sum[i] = add(sum[i+1], f[i]);
  }
  cout << f[0] << endl;
  return 0;
}
