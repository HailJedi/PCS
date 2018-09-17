#include <bits/stdc++.h>

using namespace std;

const int N = 15000 + 5;
const int X = 50000 + 5;

pair<int, int> city[N];
long long dis[N];
long long sum[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &city[i].first, &city[i].second);
  }
  sort(city+1, city+1+n);
  long long d = 0;
  for (int i = 1; i <= n; i++) {
    sum[i] = sum[i-1] + city[i].second;
    d += city[i].second * (city[i].first - city[1].first);
  }
  int ans = 1;
  for (int i = 1; i <= n; i++) {
    dis[i] = d;
    d += (city[i+1].first - city[i].first) * sum[i];
    d -= (city[i+1].first - city[i].first) * (sum[n] - sum[i]);
    if (dis[i] < dis[ans]) {
      ans = i;
    }
  }
  printf("%.5lf\n", (double)city[ans].first);
  return 0;
}
