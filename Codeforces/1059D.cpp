/*
Created 2018-10-08
"Nature Reserve"
A geometry problem with binary search solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

typedef pair<double, double> Point;

int n;
Point pt[N];

bool judge(long double R) {
  long double lp = -1e18, rp = 1e18;
  for (int i = 1; i <= n; i++) {
    if (pt[i].second > 2 * R) {
      return false;
    }
    long double dh = fabs(pt[i].second - R);
    long double l = pt[i].first - sqrt(pow(R, 2) - pow(dh, 2));
    long double r = pt[i].first + sqrt(pow(R, 2) - pow(dh, 2));
    if (l > rp || r < lp) {
      return false;
    }
    lp = max(lp, l);
    rp = min(rp, r);
  }
  return true;
}

int main() {
  scanf("%d", &n);
  bool pos = false, neg = false;
  for (int i = 1; i <= n; i++) {
    scanf("%lf %lf", &pt[i].first, &pt[i].second);
    pos |= pt[i].second >= 0;
    neg |= pt[i].second <= 0;
  }
  if (pos && neg) {
    printf("-1\n");
    return 0;
  }
  if (neg) {
    for (int i = 1; i <= n; i++) {
      pt[i].second *= -1;
    }
  }
  long double lp = 0, rp = 6e13;
  while (rp -lp > 1e-7) {
    long double mid = (lp + rp) / 2;
    if (mid == lp || mid == rp) {
      break;
    }
    if (judge(mid)) {
      rp = mid;
    } else {
      lp = mid;
    }
  }
  printf("%.7lf\n", (double)lp);
  return 0;
}
